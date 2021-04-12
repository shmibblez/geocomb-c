CC=clang++
C=clang
flags=-std=c++17 -stdlib=libc++ -Wall -Wextra -Wreorder-ctor -Isrc -Isrc/cpp
Cflags=-Isrc

hash_test: hash_test.o bindings.o icosahedron.o triangle.o phex.o point3.o
	mkdir -p builds
	$(CC) $(flags) -o builds/hash_test hash_test.o bindings.o icosahedron.o triangle.o phex.o point3.o
	make clean
	
hash_test.o: src/types.h src/cpp/enums.hpp
	$(C) $(Cflags) -c test/hash_test.c

bindings.o: src/types.h src/bindings.h src/cpp/enums.hpp src/cpp/icosahedron.hpp
	$(CC) $(flags) -c src/bindings.cpp

icosahedron.o: src/cpp/enums.hpp src/cpp/point3.hpp src/cpp/triangle.hpp
	$(CC) $(flags) -c src/cpp/icosahedron.cpp

triangle.o: src/cpp/enums.hpp src/cpp/point3.hpp
	$(CC) $(flags) -c src/cpp/triangle.cpp

phex.o: src/cpp/icosahedron.hpp src/cpp/point3.hpp
	$(CC) $(flags) -c src/cpp/phex.cpp

point3.o: src/cpp/constants.hpp src/cpp/enums.hpp
	$(CC) $(flags) -c src/cpp/point3.cpp

clean:
	rm -f *.o