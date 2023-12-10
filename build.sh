include="-Ilib/raylib/src -Ilib/lua/src"
linker="lib/raylib/src/libraylib.a lib/lua/src/liblua.a"

gcc src/*.c -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -o bin/chai $include $linker

rm -r bin/lua

cp -R ./assets bin/assets
cp -R ./lua bin/lua
