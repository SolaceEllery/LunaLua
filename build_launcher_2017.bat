
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat" x86

set QT_PATH=C:\Qt\Qt5.12.12\5.12.12\msvc2017\bin
set JOM=C:\Qt\Qt5.12.12\Tools\QtCreator\bin\jom

if not exist build-smbx-launcher\NUL md build-smbx-launcher
cd build-smbx-launcher
%QT_PATH%\qmake -spec win32-msvc CONFIG+=Win32 CONFIG+=release ../LunadllNewLauncher/SMBXLauncher/SMBXLauncher.pro
%JOM%\jom /J 4
if errorlevel 1 (
    pause
    exit 1
)

if exist build-smbx-launcher\NUL rd /S /Q deploy
md deploy
copy release\SMBXLauncher.exe deploy
cd deploy
%QT_PATH%\windeployqt --release SMBXLauncher.exe

rem ----------------------- A CLEAN-UP -----------------------

rem Bearer is for audio streaming, unneeded
rd /S /Q bearer
rem Print support is unused
rd /S /Q printsupport
rem Position is unused
rd /S /Q position
rem Icon engines are unused
rd /S /Q iconengines
rem Unneeded Image formats support for Qt itself for icons and pixmaps, QtWebEngine has own that works
del imageformats\qgifd.dll
del imageformats\qicnsd.dll
del imageformats\qjpegd.dll
del imageformats\qsvgd.dll
del imageformats\qtgad.dll
del imageformats\qtiffd.dll
del imageformats\qwbmpd.dll
del imageformats\qwebpd.dll
rem D3D Compiler is unneeded, it's already in a system
del D3Dcompiler_*.dll
rem Serial port is unused
del Qt5SerialPortd.dll
rem SVG for Qt itself is unused
del Qt5Svgd.dll
rem ----------------------- A CLEAN-UP -----------------------
cd ..

cd ..

pause
exit