@echo off

if NOT DEFINED BUILD_NUMBER (
  set MAJOR_VER=3
)

if NOT DEFINED BUILD_NUMBER (
  set MINOR_VER=0
)

if NOT DEFINED BUILD_NUMBER (
  set BUILD_NUMBER=0000
)

if NOT DEFINED OUTPUT_PATH (
  set OUTPUT_PATH=%CD%
)

if NOT DEFINED CMAKE_EXE (
  set CMAKE_EXE="C:\Program Files\CMake\bin\cmake.exe"
)

REM Setup VxSdkNet build
pushd VxSdkNet
call ..\Nuget\nuget.exe install packages.config -OutputDirectory packages -ExcludeVersion

if exist bin\ rd /q /s bin
if exist build\ rd /q /s build
mkdir build & pushd build

mkdir VxSdkNet_x86 & pushd VxSdkNet_x86
%CMAKE_EXE% -G "Visual Studio 14" ..\..\
popd

mkdir VxSdkNet_x64 & pushd VxSdkNet_x64
%CMAKE_EXE% -G "Visual Studio 14 Win64" ..\..\
popd
popd
popd

REM Setup VxSdkNet-Media build
pushd VxSdkNetMedia
call ..\Nuget\nuget.exe install packages.config -OutputDirectory packages -ExcludeVersion

if exist bin\ rd /q /s bin
if exist build\ rd /q /s build
mkdir build & pushd build

mkdir VxSdkNetMedia_x86 & pushd VxSdkNetMedia_x86
%CMAKE_EXE% -G "Visual Studio 14" ..\..\
popd

mkdir VxSdkNetMedia_x64 & pushd VxSdkNetMedia_x64
%CMAKE_EXE% -G "Visual Studio 14 Win64" ..\..\
popd
popd
popd

REM Build VxSdkNet
%CMAKE_EXE% --build VxSdkNet\build\VxSdkNet_x86 --config Release
%CMAKE_EXE% --build VxSdkNet\build\VxSdkNet_x64 --config Release

REM Build VxSdkNet-Media
%CMAKE_EXE% --build VxSdkNetMedia\build\VxSdkNetMedia_x86 --config Release
%CMAKE_EXE% --build VxSdkNetMedia\build\VxSdkNetMedia_x64 --config Release

REM Create Nuget Packages
call Nuget\nuget.exe pack Nuget\VxSdk.NET.nuspec -Version %MAJOR_VER%.%MINOR_VER%.%BUILD_NUMBER% -OutputDirectory %OUTPUT_PATH%
call Nuget\nuget.exe pack Nuget\VxSdk.NET-Media.nuspec -Version %MAJOR_VER%.%MINOR_VER%.%BUILD_NUMBER% -OutputDirectory %OUTPUT_PATH%