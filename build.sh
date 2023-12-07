include=-Ilib/raylib/src
linker=lib/raylib/src/libraylib.a

gcc src/*.c -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -o bin/chai $include $linker
