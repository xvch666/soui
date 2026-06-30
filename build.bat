rem SOUI build script (UTF-8, no BOM) -- keep this line ASCII; @echo off follows
@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion
rem ============================================================
rem  SOUI 批量编译脚本
rem  编译: Win32 Debug / Win32 Release / x64 Debug / x64 Release
rem
rem  用法:
rem    build.bat                 编译全部 4 个配置
rem    build.bat win32           仅 Win32 (Debug+Release)
rem    build.bat x64             仅 x64   (Debug+Release)
rem    build.bat debug           仅 Debug (Win32+x64)
rem    build.bat release         仅 Release (Win32+x64)
rem    build.bat win32 release   指定单配置
rem    build.bat x64 debug       指定单配置
rem    build.bat clean           清理 bin/obj 输出目录
rem    build.bat help            显示帮助
rem ============================================================

cd /d "%~dp0"
title SOUI 批量编译

rem ---------- 定位 MSBuild ----------
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "MSBUILD="
if exist "%VSWHERE%" (
    for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
        if not defined MSBUILD set "MSBUILD=%%i"
    )
)
if not defined MSBUILD (
    for %%y in (Professional Enterprise Community BuildTools Preview) do (
        for %%b in (2022 2019 2017) do (
            if not defined MSBUILD if exist "%ProgramFiles%\Microsoft Visual Studio\%%b\%%y\MSBuild\Current\Bin\MSBuild.exe" set "MSBUILD=%ProgramFiles%\Microsoft Visual Studio\%%b\%%y\MSBuild\Current\Bin\MSBuild.exe"
        )
    )
)
if not defined MSBUILD (
    echo [错误] 未找到 MSBuild。请确认已安装 Visual Studio 2017+ 或 Build Tools。
    exit /b 1
)
echo [信息] MSBuild: %MSBUILD%

set "SLN_WIN32=soui.sln"
set "SLN_X64=soui64.sln"
rem 日志按平台放入 bin(Win32) / bin64(x64)，无需单独 LOGDIR

rem ---------- 参数解析 ----------
set "ARG1=%~1"
set "ARG2=%~2"
if /i "%ARG1%"=="help" goto :usage
if /i "%ARG1%"=="/?"   goto :usage
if /i "%ARG1%"=="-h"   goto :usage
if /i "%ARG1%"=="--help" goto :usage
if /i "%ARG1%"=="clean" goto :clean

set DO_W32D=1
set DO_W32R=1
set DO_X64D=1
set DO_X64R=1

if /i "%ARG1%"=="win32" (
    set DO_X64D=0
    set DO_X64R=0
    if /i "%ARG2%"=="debug"   set DO_W32R=0
    if /i "%ARG2%"=="release" set DO_W32D=0
)
if /i "%ARG1%"=="x64" (
    set DO_W32D=0
    set DO_W32R=0
    if /i "%ARG2%"=="debug"   set DO_X64R=0
    if /i "%ARG2%"=="release" set DO_X64D=0
)
if /i "%ARG1%"=="debug" (
    set DO_W32R=0
    set DO_X64R=0
    if /i "%ARG2%"=="x64"   set DO_W32D=0
    if /i "%ARG2%"=="win32" set DO_X64D=0
)
if /i "%ARG1%"=="release" (
    set DO_W32D=0
    set DO_X64D=0
    if /i "%ARG2%"=="x64"   set DO_W32R=0
    if /i "%ARG2%"=="win32" set DO_X64R=0
)

rem ---------- 开始计时 ----------
for /f "delims=" %%e in ('powershell -NoProfile -Command "[DateTimeOffset]::UtcNow.ToUnixTimeSeconds()"') do set T_START=%%e

set PASS=0
set FAIL=0
set TOTAL=0
set "R_W32D=跳过"
set "R_W32R=跳过"
set "R_X64D=跳过"
set "R_X64R=跳过"

if "!DO_W32D!"=="1" call :build "Win32" "Debug"   "%SLN_WIN32%" "Win32" "W32D"
if "!DO_W32R!"=="1" call :build "Win32" "Release" "%SLN_WIN32%" "Win32" "W32R"
if "!DO_X64D!"=="1" call :build "x64"   "Debug"   "%SLN_X64%"   "x64"   "X64D"
if "!DO_X64R!"=="1" call :build "x64"   "Release" "%SLN_X64%"   "x64"   "X64R"

for /f "delims=" %%e in ('powershell -NoProfile -Command "[DateTimeOffset]::UtcNow.ToUnixTimeSeconds()"') do set T_END=%%e
set /a ELAPSED=T_END-T_START

echo.
echo ============================================================
echo  编译汇总  (耗时 %ELAPSED% 秒)
echo ============================================================
echo   Win32 Debug   : !R_W32D!
echo   Win32 Release : !R_W32R!
echo   x64   Debug   : !R_X64D!
echo   x64   Release : !R_X64R!
echo ------------------------------------------------------------
echo   成功 !PASS! / 失败 !FAIL! / 共 !TOTAL!
echo   日志: Win32 见 bin\,  x64 见 bin64\  (与编译产物同目录)
echo ============================================================

rem ---------- 清理中间文件 ----------
echo.
echo [清理] 删除中间产物目录 ...
if exist obj rmdir /s /q obj
if exist obj (
    echo [清理] *** obj 删除失败 ***
) else (
    echo [清理] obj 已删除
)
if exist build_logs rmdir /s /q build_logs
if exist build_logs (
    echo [清理] *** build_logs 删除失败 ***
) else (
    echo [清理] build_logs 已删除
)

if !FAIL! gtr 0 exit /b 1
exit /b 0


rem ============== 子例程:编译单个配置 ==============
:build
set "PLAT=%~1"
set "CFG=%~2"
set "SLN=%~3"
set "PLATARG=%~4"
set "KEY=%~5"
set "TAG=%PLAT%-%CFG%"
if "%PLAT%"=="Win32" (set "LOG=bin\%TAG%.log") else (set "LOG=bin64\%TAG%.log")

echo.
echo [%TAG%] 开始编译 ...  %time%
echo [%TAG%] >> "%LOG%"
echo ===== %TAG%  %date% %time% ===== >> "%LOG%"

"%MSBUILD%" "%SLN%" /t:Rebuild /p:Configuration=%CFG% /p:Platform=%PLATARG% /m /v:m /nologo /fl /flp:"logfile=%LOG%;verbosity=minimal;Encoding=UTF-8"
set "RC=!errorlevel!"

set /a TOTAL+=1
if "!RC!"=="0" (
    call set "R_!KEY!=成功"
    set /a PASS+=1
    echo [%TAG%] 编译成功  [%time%]
    echo [%TAG%] 结果: 成功 >> "%LOG%"
) else (
    call set "R_!KEY!=失败"
    set /a FAIL+=1
    echo [%TAG%] *** 编译失败 *** errorlevel=!RC!  日志见 %LOG%
    echo [%TAG%] 结果: 失败 errorlevel=!RC! >> "%LOG%"
)
goto :eof


rem ============== 清理 ==============
:clean
echo [清理] 删除 bin, bin64, obj, build_logs 目录 ...
if exist bin   rmdir /s /q bin
if exist bin64 rmdir /s /q bin64
if exist obj   rmdir /s /q obj
if exist build_logs rmdir /s /q build_logs
echo [清理] 完成
exit /b 0


rem ============== 帮助 ==============
:usage
echo 用法: %~nx0 [选项]
echo.
echo   (无参数)          编译全部 4 个配置
echo   win32             仅 Win32 (Debug + Release)
echo   x64               仅 x64   (Debug + Release)
echo   debug             仅 Debug (Win32 + x64)
echo   release           仅 Release (Win32 + x64)
echo   win32 release     仅 Win32 Release
echo   x64 debug         仅 x64 Debug
echo   clean             清理 bin/bin64/obj/build_logs
echo   help              显示本帮助
exit /b 0
