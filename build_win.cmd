set PRJ_DIR_WIN=%cd%
set PRJ_DIR=%PRJ_DIR_WIN:\=/%
set BUILD_DIR=%PRJ_DIR_WIN%\build

set VS_DIR=C:/Program Files/Microsoft Visual Studio/2022/Community/VC
set VS_BIN_DIR=%VS_DIR%/Tools/MSVC/14.34.31933/bin/Hostx64/x64
set VS_LIBS=%VS_DIR%/Tools/MSVC/14.34.31933/lib/x64
set ABI_PATH=%VS_DIR:/=\%\Auxiliary\Build\vcvarsall.bat

call "%ABI_PATH%" x64 -vcvars_ver=14.29
@echo on

set QT_DIR=C:/Qt/5.15.2/msvc2019_64
set "LIB=%VS_LIBS:/=\%;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\ucrt\x64"
set "PATH=%PATH%;%QT_DIR:/=\%\bin;C:\Qt\Tools\Ninja"

rmdir /s /q %BUILD_DIR%
mkdir %BUILD_DIR%

cd %BUILD_DIR%
set BUILD_DIR=%BUILD_DIR:\=/%

cmake -G "Ninja" -S %PRJ_DIR% -B %BUILD_DIR% -DCMAKE_PREFIX_PATH:STRING=%QT_DIR%; -DQT_QMAKE_EXECUTABLE:STRING=%QT_DIR%/bin/qmake.exe -DCMAKE_C_COMPILER:STRING="%VS_BIN_DIR%/cl.exe" -DCMAKE_CXX_COMPILER:STRING="%VS_BIN_DIR%/cl.exe" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX:STRING=%BUILD_DIR%"
cmake --build %BUILD_DIR% --target all

%QT_DIR%/bin/windeployqt.exe --release --qmldir %PRJ_DIR%/src %BUILD_DIR%/sudoku.exe

pause
