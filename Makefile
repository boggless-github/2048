all: build src/2048.cpp
	g++ -I./inc src/2048.cpp -o 2048.exe

build:
	mkdir build

run: all
	./2048.exe