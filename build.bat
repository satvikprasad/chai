@echo off

SET include=-Ilib\raylib\src
SET linker=lib\raylib\src\libraylib.a -lgdi32 -lole32 -loleaut32 -llmm32 -lwinmm

gcc src\*.c -o bin\chai %include% %linker%
