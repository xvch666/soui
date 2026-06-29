# SOUI 控件及核心类完整清单

## 一、基础控件（SOUI/include/control/）

| 类名 | XML 标签 | 父类 | 说明 |
|------|----------|------|------|
| SStatic | text | SWindow | 静态文本 |
| SLink | link | SWindow | 超链接 |
| SButton | button | SWindow | 按钮 |
| SImageButton | imgbtn | SButton | 图片按钮 |
| SImageWnd | img | SWindow | 图片显示 |
| SAnimateImgWnd | animateimg | SWindow | 动画图片 |
| SProgress | progress | SWindow | 进度条 |
| SLine | hr | SWindow | 分割线 |
| SCheckBox | check | SWindow | 复选框 |
| SIconWnd | icon | SWindow | 图标 |
| SRadioBox | radio | SWindow | 单选按钮 |
| SToggle | toggle | SWindow | 开关切换 |
| SGroup | group | SWindow | 分组容器 |
| SEdit | edit | SRichEdit | 单行编辑框 |
| SRichEdit | richedit | SPanel | 富文本编辑框 |
| SComboBox | combobox | SComboBase | 下拉组合框 |
| SComboView | comboview | SComboBase | 下拉视图 |
| SComboBase | combobase | SWindow | 下拉框基类 |
| SListBox | listbox | SScrollView | 列表框 |
| SListCtrl | listctrl | SPanel | 列表控件 |
| SListView | listview | SPanel | 列表视图 |
| SMCListView | mclistview | SPanel | 多列列表视图 |
| STreeCtrl | treectrl | SScrollView | 树形控件 |
| STreeView | treeview | SPanel | 树形视图 |
| STabCtrl | tabctrl | SWindow | 选项卡控件 |
| STabPage | page | SWindow | 选项卡页面 |
| SScrollBar | scrollbar | SWindow | 滚动条 |
| SSliderBar | sliderbar | SProgress | 滑块条 |
| SSpinButtonCtrl | spinButton | SWindow | 微调按钮 |
| SHeaderCtrl | header | SWindow | 列表头控件 |
| SHotKeyCtrl | hotkey | SWindow | 热键输入 |
| SCalendar | calendar | SWindow | 日历 |
| SCalendarEx | calendarex | SWindow | 增强日历 |
| SDateTimePicker | dateTimePicker | SWindow | 日期时间选择器 |
| SCaption | caption | SWindow | 标题栏 |
| SMenuBar | menubar | SWindow | 菜单栏 |
| SSplitWnd | splitwnd | SWindow | 分割窗口 |
| SSplitPane | pane | SWindow | 分割面板 |
| SSplitWnd_Col | splitcol | SSplitWnd | 纵向分割窗口 |
| SSplitWnd_Row | splitrow | SSplitWnd | 横向分割窗口 |
| STileView | tileview | SPanel | 平铺视图 |
| SActiveX | activex | SWindow | ActiveX 容器 |
| SFlashCtrl | flash | SActiveX | Flash 控件 |
| SRealWnd | realwnd | SWindow | 真窗口嵌入 |
| SMenuExItem | menuItem | SWindow | 菜单项 |

## 二、扩展控件（controls.extend/）

| 类名 | XML 标签 | 说明 |
|------|----------|------|
| SWindowEx | windowex | 增强窗口 |
| SAniWindow | AniWindow | 动画窗口 |
| SAnimImg | anmimg | 动画图片控件 |
| SButtonEx | buttonex | 增强按钮 |
| SCalendar2 | calendar2 | 日历 v2 |
| SChatEdit | chatedit | 聊天编辑框 |
| SChromeTabCtrl | chromeTabCtrl | Chrome 风格标签控件 |
| SComboBoxEx | comboboxex | 增强组合框 |
| SMaskEdit | maskedit | 掩码编辑框 |
| SDateEdit | dateedit | 日期编辑框 |
| STimeEdit | timeedit | 时间编辑框 |
| SFadeFrame | fadeframe | 淡入淡出框 |
| SFreeMoveWindow | freeMoveWindow | 自由移动窗口 |
| SGifPlayer | gifplayer | GIF 播放器 |
| SGroupList | groupList | 分组列表 |
| SIECtrl | iectrl | IE 浏览器控件 |
| SImageMaskWnd | imageMask | 图片遮罩窗口 |
| SImagePlayer | imgplayer | 图片播放器 |
| SIPAddressCtrl | ipctrl | IP 地址输入控件 |
| SItemBox | itembox | 项目盒子 |
| SListBoxEx | listboxex | 增强列表框 |
| SListCtrlEx | listctrlex | 增强列表控件 |
| SMCListViewEx | mclistviewex | 增强多列列表视图 |
| SLoopButton | loopbtn | 循环按钮 |
| SProgressRing | progressRing | 环形进度条 |
| SRadioBox2 | radio2 | 增强单选按钮 |
| SRatingBar | ratingbar | 评分条 |
| SScrollText | scrolltext | 滚动文字 |
| SSplitBar | splitbar | 分割条 |
| STabCtrl2 | tabctrl2 | 选项卡 v2 |
| STabPage2 | page2 | 选项卡页 v2 |
| STextEx | textex | 增强文本 |
| STreeBox | treebox | 树形选择框 |
| STurn3dView | Turn3dView | 3D 翻转视图 |
| SWkeWebkit | wkeWebkit | Webkit 浏览器控件 |
| SHeaderCtrlEx | header2 | 增强列表头 |
| SChromeTab | chromeTab | Chrome 标签页 |
| SImageEx | imgex | 增强图片 |
| SEditIP | ipedit | IP 编辑框 |

## 三、属性网格（controls.extend/propgrid/）

| 类名 | XML 标签 | 说明 |
|------|----------|------|
| SPropertyGrid | propgrid | 属性网格 |
| SPropertyGroup | propgroup | 属性分组 |
| SPropertyItemBase | propitembase | 属性项基类 |
| SPropertyItemText | proptext | 文本属性项 |
| SPropertyItemColor | propcolor | 颜色属性项 |
| SPropertyItemOption | propoption | 选项属性项 |
| SPropertyItemSize | propsize | 尺寸属性项 |

## 四、核心窗口（SOUI/include/core/）

| 类名 | XML 标签 | 父类 | 说明 |
|------|----------|------|------|
| SWindow | window | SObject | 窗口基类 |
| SHostWnd | hostwnd | SwndContainerImpl | 宿主窗口（带 HWND） |
| SHostDialog | hostdlg | SHostWnd | 宿主模态对话框 |
| SPanel | div | SWindow | 面板 / DIV 容器 |
| SScrollView | scrollview | SPanel | 滚动视图 |
| SItemPanel | itemPanel | SwndContainerImpl | 列表项模板宿主 |
| SwndContainerImpl | SwndContainerImpl | SWindow | 窗口容器实现 |
| SHostWndAttr | SHostWndAttr | SObject | 宿主窗口属性 |
| SwndStyle | style | SObject | 窗口样式管理器 |

## 五、布局（SOUI/include/layout/）

| 类名 | XML 标签 | 说明 |
|------|----------|------|
| SLinearLayout | linearLayout | 线性布局 |
| SVBox | vbox | 垂直布局 |
| SHBox | hbox | 水平布局 |
| SGridLayout | gridLayout | 网格布局 |
| SouiLayout | SouiLayout | SOUI 自研布局 |
| SLinearLayoutParam | LinearLayoutParam | 线性布局参数 |
| SGridLayoutParam | GridLayoutParam | 网格布局参数 |
| SouiLayoutParam | SouiLayoutParam | Soui 布局参数 |

## 六、Skin 皮肤类

| 类名 | XML 标签 | 说明 |
|------|----------|------|
| SSkinObjBase | skinObjBase | 皮肤基类 |
| SSkinImgList | imglist | 图片列表皮肤 |
| SSkinImgFrame | imgframe | 九宫格皮肤 |
| SSkinImgFrame2 | imgframe2 | 九宫格皮肤 v2 |
| SSkinImgFrame3 | imgframe3 | 九宫格皮肤 v3 |
| SSkinImgCenter | imgCenter | 居中图片皮肤 |
| SSkinButton | button | 按钮皮肤 |
| SSkinGradation | gradation | 渐变皮肤 |
| SSkinScrollbar | scrollbar | 滚动条皮肤 |
| SSkinNewScrollbar | newScrollbar | 新滚动条皮肤 |
| SSkinVScrollbar | vscrollbar | 垂直滚动条皮肤 |
| SSkinColorRect | colorrect | 纯色矩形皮肤 |
| SSkinShape | shape | 形状皮肤 |
| SSkinGroup | group | 皮肤组合 |
| SSkinGif | gif | GIF 皮肤 |
| SSkinAPNG | apng | APNG 皮肤 |
| SSkinAni | skinani | 动画皮肤基类 |
| SColorMask | colormask | 颜色遮罩 |
| SSkinMutiFrameImg | imgMutiFrame | 多帧图片皮肤 |

## 七、插值器（动画，SOUI/include/animator/）

| 类名 | XML 标签 | 说明 |
|------|----------|------|
| SInterpolatorBase | interpolator_base | 插值器基类 |
| SLinearInterpolator | Linear | 线性插值 |
| SAccelerateInterpolator | Accelerate | 加速插值 |
| SDecelerateInterpolator | Decelerate | 减速插值 |
| SAccelerateDecelerateInterpolator | AccelerateDecelerate | 先加速后减速 |
| SAnticipateInterpolator | Anticipate | 回弹插值 |
| SAnticipateOvershootInterpolator | AnticipateOvershoot | 回弹超出插值 |
| SBounceInterpolator | Bounce | 弹跳插值 |
| SCycleInterpolator | Cycle | 循环插值 |
| SOvershootInterpolator | Overshoot | 超出插值 |

## 八、事件类（SOUI/include/event/）

| 类名 | XML 标签 | 说明 |
|------|----------|------|
| EventArgs | eventargs | 事件基类 |
| EventCmnArgs | — | 通用事件参数 |
| EventCalendarSelDay | on_calendar_sel_day | 日历选择日期 |
| EventCalendarSetDate | on_calendar_set_date | 日历设置日期 |
| EventCalendarExChanged | on_calendarex_changed | 增强日历变更 |
| EventChatEditKeyReturn | on_chatedit_key_return | 聊天编辑回车 |
| EventChromeTabNew | on_chrometab_new | Chrome 标签新建 |
| EventChromeTabClose | on_chrometab_close | Chrome 标签关闭 |
| EventChromeTabSelChanged | on_chrometab_sel_changed | Chrome 标签切换 |
| EventChromeTabDbClick | on_chrometab_dbclick | Chrome 标签双击 |
| EventOfComoboxExItem | on_event_of_comboxex_item | 增强下拉选项 |
| EventLBGetDispInfo | on_listbox_get_display_info | 列表框获取显示信息 |
| EventTBGetDispInfo | on_treebox_get_display_info | 树形框获取显示信息 |
| EventTBSelChanging | on_treebox_sel_changing | 树形框选择变更中 |
| EventTBSelChanged | on_treebox_sel_changed | 树形框选择已变更 |
| EventTBQueryItemHeight | on_treebox_query_item_height | 树形框查询项高度 |
| EventTCSelChanging | on_btn_sel_changing | 循环按钮选择变更中 |
| EventTCSelChanged | on_btn_sel_changed | 循环按钮选择已变更 |
| EventPropGridValueChanged | on_propgrid_value_changed | 属性网格值变更 |
| EventTurn3d | on_turn3d | 3D 翻转事件 |

---

总计：45 个核心控件 + 38 个扩展控件 + 7 个属性网格 + 9 个核心窗口 + 8 个布局 + 19 个皮肤 + 10 个插值器 + 20 个事件类 = 156 个可注册类
