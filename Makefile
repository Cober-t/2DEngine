build:
	g++ -Wall -std=c++17 src/*.cpp -I"./libs/" -lSDL2 -llua5.4 -lGL -lGLEW -o 2DEngine

run:
	./2DEngine
	

clean:
	rm 2DEngine
