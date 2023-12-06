@echo off

SET include=-Ilib\raylib\src
SET linker=lib\raylib\src\libraylib.a

gcc src\*.c -o bin\chai %include% %linker%
