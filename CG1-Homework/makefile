# The compiler to use
CC = clang++

# Compiler flags
CFLAGS = -Wall -std=c++17

# The build target executable
TARGET = RemakeV1

all: $(TARGET)

$(TARGET): RemakeV1.o vec3Math.o
	$(CC) $(CFLAGS) -o $(TARGET) RemakeV1.o vec3Math.o

RemakeV1.o: RemakeV1.cpp vec3Math.hpp
	$(CC) $(CFLAGS) -c RemakeV1.cpp

vec3Math.o: vec3Math.cpp vec3Math.hpp
	$(CC) $(CFLAGS) -c vec3Math.cpp

clean:
	$(RM) $(TARGET) *.o *~

# CC = g++: This line sets the compiler to g++. You can replace this with any C++ compiler you prefer.

# CFLAGS = -Wall -std=c++11: These are the flags that will be passed to the compiler. -Wall enables all warnings and -std=c++11 sets the language standard to C++11.

# TARGET = RemakeV1: This is the name of the final executable that will be created.

# all: $(TARGET): This is a target that depends on $(TARGET). When you run make or make all, it will build the $(TARGET) (in this case, RemakeV1).
# $(TARGET): RemakeV1.o vec3Math.o: This line tells make how to build $(TARGET) from RemakeV1.o and vec3Math.o.

# RemakeV1.o: RemakeV1.cpp vec3Math.hpp and vec3Math.o: vec3Math.cpp vec3Math.hpp: These lines tell make how to build the .o files from your .cpp and .hpp files.

# clean:: This is a phony target (it’s not a file name), which is a command for cleaning up your build. Running make clean will remove the executable and all .o files.