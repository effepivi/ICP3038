rm -f main.o
rm -f Window.o
rm -f example1

g++ -c  -Iinclude/ src/Window.cpp
g++ -c  -Iinclude/ src/main.cpp

if [[ `uname -s` == 'Darwin' ]]; then
    g++ -o example1 main.o Window.o -framework OpenGL -framework GLUT
else
    g++ -o example1 main.o Window.o -lGL -lglut
fi
