all: main

main: superMario.cpp
	g++ superMario.cpp -w -lSDL2 -lSDL2_image -o main

clean:
	rm main
