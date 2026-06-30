# SOUI 架构说明

本文档描述 SOUI 的整体架构、分层、组件模型，以及平台/线程约束与扩展方式。
类清单请参见 [`controls.md`](./controls.md)。

## 一、项目定位

SOUI 是一个 **Windows 原生 DirectUI GUI 框架**。采用 **COM 风格的 C++ 组件化架构**：
渲染后端可替换、资源/皮肤/布局/控件通过反射式工厂由 XML 驱动实例化、所有跨模块对象以
引用计数管理生命周期。

## 二、分层架构

依赖严格向内收敛，外层可依赖内层，反之禁止：

```
demo / 应用层
   │
controls.extend  (38 扩展控件 + propgrid)
   │
components       (render-skia / render-gdi / imgdecoder-* / translator / log4z / TaskLoop / SIpcObject)
   │  ▲ 通过 interface 抽象绑定（运行期 DLL 或静态库）
   ▼ │
SOUI 核心        (SWindow 窗口树 / layout / event / control / res.mgr / interface)
   │
utilities        (IObjRef 引用计数 / SObject 反射基类 / string / collection / mini ATL·WTL)
```

- **utilities**：零业务依赖的基础设施。`IObjRef` + `TObjRefImpl` + `CAutoRefPtr` 提供引用计数；
  `SObjectImpl<T>` 提供运行期类型识别与 XML 属性分派。
- **SOUI 核心**：窗口系统、布局、事件、资源管理、控件基类与抽象接口（`SOUI/include/interface/`）。
- **components**：可替换的实现模块，每个实现核心层定义的接口（渲染、图像解码、翻译、日志、任务循环）。
- **controls.extend**：基于核心层控件基类的扩展控件。

## 三、组件模型

### 3.1 引用计数

跨模块对象继承 `IObjRef`，由 `TObjRefImpl<T>` 提供 `AddRef/Release/OnFinalRelease`，
`CAutoRefPtr<T>` 是 intrusive 智能指针。生命周期由引用计数决定，跨 DLL 边界安全。

### 3.2 反射式工厂

`SObjectFactoryMgr` 维护 `SObjectInfo(name,type) → SObjectFactory` 映射。每个可 XML 实例化的类通过
`SOUI_CLASS_NAME_EX` 宏登记类名与类型，`TplSObjectFactory<T>` 提供创建。`SApplication` 在构造时
通过 `ISystemObjectRegister` 注册全部系统控件/皮肤/布局/插值器。

### 3.3 组件加载

`components/com-cfg.h` 的 `SComMgr` 支持两种链接方式：
- `LIB_SOUI_COM`：静态链接各组件库；
- 否则：运行期通过 `SComLoader` 从 DLL 的 `SCreateInstance` 符号加载。

## 四、渲染抽象

`IRenderFactory` 创建设备相关资源与 `IRenderTarget`。GDI 与 Skia 双后端实现同一套接口。

### 4.1 能力子接口（ISP 拆分）

`IRenderTarget` 聚合 12 个职责单一的能力子接口，新代码可针对所需窄接口编程
（如 `IRenderText&`），既有调用点继续使用 `IRenderTarget*` 不变：

| 子接口 | 职责 |
|--------|------|
| `IRenderResources` | pen / brush / region 工厂 |
| `IRenderSurface` | resize、HDC 互操作 |
| `IRenderTransform` | 视口原点、变换矩阵 |
| `IRenderClip` | 矩形/区域/路径裁剪 |
| `IRenderText` | 文本测量与输出 |
| `IRenderPrimitives` | 矩形/圆角/椭圆/弧/折线 |
| `IRenderBitmap` | 位图/图标绘制与位块 |
| `IRenderGradient` | 线性/多色/径向渐变 |
| `IRenderPath` | 路径描边与填充 |
| `IRenderState` | GDI 对象选择、xfermode |
| `IRenderPixel` | 像素读写 |
| `IRenderLayer` | 离屏图层 push/pop |

新增渲染后端需实现 `IRenderTarget` 全部方法（仍为单一具体类，vtable 经 mix-in 继承组织）。

## 五、窗口系统

`SWindow`（`SOUI/include/core/Swnd.h`）是所有窗口与控件的基类，维护窗口树、布局、绘制、
消息分派、属性解析、状态。宿主窗口 `SHostWnd` 拥有真实 HWND。

`SWindow` 的渲染缓存状态（分层/缓存 RenderTarget、窗口 Region、无效区域、缓存标志）已从
God Object 抽出为内聚的复合对象 `SwndRenderCache`（`SWindow::m_renderCache`），仅供渲染管线
内部使用，派生类不应直接访问。

`Swnd.cpp` 的 RenderTarget/分层窗口管理函数已拆分至 `src/core/SwndRender.cpp`。
其余大文件（`shostwnd.cpp`、`SMenuEx.cpp`、`STreeCtrl.cpp`、`STreeView.cpp`）目前各为单一类内聚单元，
拆分收益有限，后续如需拆分请沿用 `SwndRender.cpp` 的约定：
按连续内聚函数簇迁移、新文件镜像 `souistd.h` 预编译头、并在对应 `.vcxproj` 注册。

## 六、应用上下文与解耦

`SApplication` 是核心单例，同时是 `SResProviderMgr` 与 `SObjectFactoryMgr`。

便捷宏（`GETRENDERFACTORY` / `GETCOLOR` / `GETSTRING` / `LOADIMAGE` / `LOADXML` 等）**经
`SApplication::GetCurrentApp()` 间接路由**，而非直接耦合单例。`GetCurrentApp()` 返回可安装的
当前应用指针：未显式设置时回退到单例；调用 `SetCurrentApp(SApplication*)` 可在运行期重定向
所有 `GET*` / `LOAD*` 宏的目标应用对象（支持多实例 / 依赖注入 / 测试替身）。
`SApplication` 构造时将自身注册为当前上下文。

## 七、平台支持

- **最低目标**：Windows 7（`WINVER = _WIN32_WINNT = 0x0601`）。**Windows XP / 2000 不再支持。**
- 工具集：Visual Studio 2022（`v143`）。生成用户工程的 `wizard/` 模板已统一为 `v143`。
- 旧的 `tools/ConvertPlatformToXp` 为 XP 时代遗留工具，已不再需要。
- 可访问性（MSAA，`SOUI_ENABLE_ACC`）为编译期可选项，默认关闭；需要时在
  `SOUI/include/souistd.h` 取消该宏注释并重新编译。

## 八、线程模型

SOUI 是**单 UI 线程**框架：所有窗口对象的创建、布局、绘制、消息处理必须在同一线程
（宿主窗口所在线程）完成。`SWindow::TestMainThread()` 在 Debug 构建中校验关键操作的线程一致性。
跨进程通信由 `components/SIpcObject` 提供；后台任务由 `components/TaskLoop` 提供独立线程循环，
但其回调中如需操作 UI，必须切回 UI 线程。

## 九、扩展指南

| 扩展类型 | 做法 |
|----------|------|
| 自定义控件 | 继承 `SWindow`（或具体控件基类），`SOUI_CLASS_NAME_EX` 登记类名，`SApplication::RegisterWindowClass<T>()` 注册 |
| 自定义皮肤 | 继承 `SSkinObjBase`，`RegisterSkinClass<T>()` 注册 |
| 自定义布局 | 实现 `ILayout` + `ILayoutParam`，`RegisterLayout` 注册 |
| 新渲染后端 | 实现 `IRenderFactory` 与 `IRenderTarget`（全部能力子接口），通过 `SComMgr` 暴露 |
| 新图像解码器 | 实现 `IImgDecoderFactory`，经 `SComMgr::CreateImgDecoder` 选择 |

## 十、源文件编码约定

仓库源文件多为 **UTF-8（无 BOM）**。MSVC 在未指定 `/utf-8` 时按系统区域设置解释无 BOM 文件，
部分 UTF-8 中文字节可能被误读为 GBK 而触发 `C3872`。新增代码注释建议：
- 优先使用 ASCII 注释；如需中文，确保整文件编码一致，或为文件添加 UTF-8 BOM。
- 切勿在 `/* */` 注释内出现 `*/` 字符序列（如 "GET*/LOAD*"），会提前闭合注释。
