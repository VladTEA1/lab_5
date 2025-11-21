@echo off
chcp 65001

set CMAKE_EXE="C:\Program Files\CMake\bin\cmake.exe"

if exist build rmdir /s /q build
mkdir build
cd build

%CMAKE_EXE% -G "MinGW Makefiles" ..
%CMAKE_EXE% --build .

if exist stack_test.exe stack_test.exe
if exist stack_demo.exe stack_demo.exe

pause