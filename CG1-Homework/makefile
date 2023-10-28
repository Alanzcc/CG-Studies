ALL: test

test: test.o vec3Math.o
	g++ -o test test.o vec3Math.o

test.o: test.cpp vec3Math.cpp vec3Math.hpp
	g++ -c test.cpp

vec3Math.o: vec3Math.cpp vec3Math.hpp
	g++ -c vec3Math.cpp

clean:
	rm -rf *.o test