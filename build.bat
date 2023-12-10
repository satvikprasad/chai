@echo off

SET include=-Ilib\raylib\src -Ilib\lua\src
SET linker=lib\raylib\src\libraylib.a lib\lua\src\liblua.a -lgdi32 -lole32 -loleaut32 -limm32 -lwinmm

gcc src\*.c -o bin\chai %include% %linker%

mkdir .\bin\assets
xcopy .\assets .\bin\assets /S /E /H

mkdir .\bin\lua
xcopy .\lua .\bin\lua /S /E /H

