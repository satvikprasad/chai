@echo off

SET include=-Ilib\raylib\src
SET linker=lib\raylib\src\libraylib.a gdi32.lib coredll.lib

gcc src\*.c -o bin\chai %include% %linker%
