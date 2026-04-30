@echo off
setlocal EnableExtensions EnableDelayedExpansion
cd /d "%~dp0"
set "PF86=%ProgramFiles(x86)%"

where cl.exe >nul 2>nul
if errorlevel 1 (
  set "VSWHERE=!PF86!\Microsoft Visual Studio\Installer\vswhere.exe"
  if not exist "!VSWHERE!" (
    if exist "!PF86!\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" set "VSDEVCMD=!PF86!\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    if exist "!PF86!\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" set "VSDEVCMD=!PF86!\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat"
    if exist "!PF86!\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat" set "VSDEVCMD=!PF86!\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
    if exist "!PF86!\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat" set "VSDEVCMD=!PF86!\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat"

    if not defined VSDEVCMD (
      echo cl.exe was not found. Run this from a Visual Studio Developer Command Prompt.
      exit /b 1
    )
  ) else (
    for /f "usebackq tokens=*" %%i in (`"!VSWHERE!" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSINSTALL=%%i"
    if not defined VSINSTALL (
      echo Visual Studio with MSVC tools was not found.
      exit /b 1
    )
    set "VSDEVCMD=!VSINSTALL!\Common7\Tools\VsDevCmd.bat"
  )

  call "!VSDEVCMD!" -arch=x64 -host_arch=x64
  if errorlevel 1 exit /b 1
)

if not exist build\msvc mkdir build\msvc

cl.exe /nologo /EHsc /std:c++17 /TP /W3 ^
  /Fo:build\msvc\ ^
  /I"ModelView\include" ^
  /IcommonLib\include ^
  /IcommonLib\include\math\algebra\primitives ^
  /IcommonLib\include\Polygon ^
  /IcommonLib\include\String ^
  /IcommonLib\include\UI ^
  "ModelView\src\main.c" ^
  "ModelView\src\renderer.c" ^
  commonLib\src\UI\clCamera.c ^
  commonLib\src\Polygon\clMesh.c ^
  commonLib\src\Polygon\clRenderObject.c ^
  commonLib\src\String\clString.c ^
  commonLib\src\math\algebra\primitives\clV3.c ^
  /Fe:ModelView_msvc.exe ^
  /link /SUBSYSTEM:WINDOWS winmm.lib wininet.lib user32.lib kernel32.lib shell32.lib gdi32.lib opengl32.lib
if errorlevel 1 exit /b 1

echo Built ModelView_msvc.exe
