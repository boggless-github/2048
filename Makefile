ifeq ($(OS), Windows_NT)
	OSDEF=WINDOWS
else 
	OSDEF=LINUX
endif

all: build src/2048.cpp
	g++ -I./inc src/2048.cpp -o 2048.exe -D $(OSDEF)

build:
	mkdir build

run: all
	./2048.exe