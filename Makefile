all: main

main: test.cpp
	g++ test.cpp -w -lSDL2 -lSDL2_image

clean:
	rm a.out
