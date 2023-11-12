# The compiler to use
CC = clang++

# Compiler flags
CFLAGS = -Wall -std=c++17

# The build target executable
TARGET = main

all: $(TARGET)

$(TARGET): main.o Canvas.o Sphere.o Ray.o vec3Math.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o Canvas.o Sphere.o Ray.o vec3Math.o

main.o: main.cpp Canvas.hpp Sphere.hpp Ray.hpp
	$(CC) $(CFLAGS) -c main.cpp

Canvas.o: Canvas.cpp Canvas.hpp Sphere.hpp Ray.hpp
	$(CC) $(CFLAGS) -c Canvas.cpp

Sphere.o: Sphere.cpp Sphere.hpp Ray.hpp vec3Math.hpp
	$(CC) $(CFLAGS) -c Sphere.cpp

Ray.o: Ray.cpp Ray.hpp vec3Math.hpp
	$(CC) $(CFLAGS) -c Ray.cpp

vec3Math.o: vec3Math.cpp vec3Math.hpp
	$(CC) $(CFLAGS) -c vec3Math.cpp

#Matrix.o: Matrix.cpp Matrix.hpp
#	$(CC) $(CFLAGS) -c Matrix.cpp

clean:
	$(RM) $(TARGET) *.o *~

# CC = g++: This line sets the compiler to g++. You can replace this with any C++ compiler you prefer.

# CFLAGS = -Wall -std=c++11: These are the flags that will be passed to the compiler. -Wall enables all warnings and -std=c++11 sets the language standard to C++11.

# TARGET = main: This is the name of the final executable that will be created.

# all: $(TARGET): This is a target that depends on $(TARGET). When you run make or make all, it will build the $(TARGET) (in this case, main).
# $(TARGET): main.o vec3Math.o: This line tells make how to build $(TARGET) from main.o and vec3Math.o.

# main.o: main.cpp vec3Math.hpp and vec3Math.o: vec3Math.cpp vec3Math.hpp: These lines tell make how to build the .o files from your .cpp and .hpp files.

# clean:: This is a phony target (it’s not a file name), which is a command for cleaning up your build. Running make clean will remove the executable and all .o files.