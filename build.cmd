@echo off
setlocal
cd /d "%~dp0"

cpc.exe ^
  -I"ModelView\include" ^
  -IcommonLib\include ^
  -IcommonLib\include\math\algebra\primitives ^
  -IcommonLib\include\Polygon ^
  -IcommonLib\include\String ^
  -IcommonLib\include\UI ^
  "ModelView\src\main.c" ^
  "ModelView\src\renderer.c" ^
  commonLib\src\UI\clCamera.c ^
  commonLib\src\Polygon\clMesh.c ^
  commonLib\src\Polygon\clRenderObject.c ^
  commonLib\src\String\clString.c ^
  commonLib\src\math\algebra\primitives\clV3.c ^
  -o "ModelView.exe" ^
  -lwinmm -lwininet -luser32 -lkernel32 -lshell32 -lgdi32 -lopengl32
if errorlevel 1 exit /b 1

echo Built ModelView.exe
