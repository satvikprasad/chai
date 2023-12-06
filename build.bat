@echo off

SET include=-Ilib\raylib\src
SET linker=-Ilib\raylib\src\libraylib.a

gcc src\*.c -o bin\chai %include% %linker%
