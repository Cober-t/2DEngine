build:
	g++ -Wall -std=c++17 src/*.cpp -I"./libs/" -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.4 -o 2DEngine

run:
	./2DEngine
	

clean:
	rm 2DEngine
