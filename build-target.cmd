@echo off

if not defined BUILD_TARGET (
  REM Change to VxSdkNetMedia to build VxSdk.NET-Media.
  set BUILD_TARGET=VxSdkNet
)

if not defined MAJOR_VER (
  set MAJOR_VER=3
)

if not defined MINOR_VER (
  set MINOR_VER=0
)

if not defined BUILD_NUMBER (
  set BUILD_NUMBER=0000
)

if not defined OUTPUT_PATH (
  set OUTPUT_PATH="%CD%\output"
)

if not defined CMAKE_EXE (
  set CMAKE_EXE="C:\Program Files\CMake\bin\cmake.exe"
)

REM Update assembly version number
powershell -Command "(gc %BUILD_TARGET%\Source\%BUILD_TARGET%.rc) -replace '12345', '%BUILD_NUMBER%' | Out-File %BUILD_TARGET%\Source\%BUILD_TARGET%.rc"

REM Create the output path for the NuGet package if it doesn't exist
if not exist %OUTPUT_PATH% mkdir %OUTPUT_PATH%

REM Setup target project build
pushd %BUILD_TARGET%
call ..\Nuget\nuget.exe install packages.config -OutputDirectory packages -ExcludeVersion

if exist bin\ rd /q /s bin
if exist build\ rd /q /s build
mkdir build & pushd build

mkdir %BUILD_TARGET%_x86 & pushd %BUILD_TARGET%_x86
%CMAKE_EXE% -G "Visual Studio 14" ..\..\
popd

mkdir %BUILD_TARGET%_x64 & pushd %BUILD_TARGET%_x64
%CMAKE_EXE% -G "Visual Studio 14 Win64" ..\..\
popd
popd
popd

REM Build target project
%CMAKE_EXE% --build %BUILD_TARGET%\build\%BUILD_TARGET%_x86 --config Release
%CMAKE_EXE% --build %BUILD_TARGET%\build\%BUILD_TARGET%_x64 --config Release

REM Create Nuget Package
if %BUILD_TARGET% == VxSdkNet (
  call Nuget\nuget.exe pack Nuget\VxSdk.NET.nuspec -Version %MAJOR_VER%.%MINOR_VER%.%BUILD_NUMBER% -OutputDirectory %OUTPUT_PATH%
) else (
  call Nuget\nuget.exe pack Nuget\VxSdk.NET-Media.nuspec -Version %MAJOR_VER%.%MINOR_VER%.%BUILD_NUMBER% -OutputDirectory %OUTPUT_PATH%
)
