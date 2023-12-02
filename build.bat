@echo off

SET INCLUDE_FLAGS=-ID:\lib\cglm\include -ID:\lib\curl\include -ID:\lib\raylib\raylib\src -ID:\lib\cimgui -ID:\lib\lua-5.4.6\src
SET LINKER_FLAGS=D:\lib\raylib\raylib\projects\VS2022\build\raylib\bin\x64\Release.DLL\raylib.lib D:\lib\curl\lib\*.a D:\lib\cglm\build\Release\cglm.lib D:\lib\cimgui\Release\cimgui.lib D:\lib\lua-5.4.6\src\lua.lib

if exist bin\chai.exe del bin\chai.exe

cl src\*.c -o bin\chai.exe /DEBUG:FULL /Z7 %INCLUDE_FLAGS% %LINKER_FLAGS%

if exist *.obj del *.obj
