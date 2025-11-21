@echo off
if exist build rmdir /s /q build
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
stack_test.exe
stack_demo.exe
pause