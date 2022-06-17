ROOT=-I .
LIB=-I ./libs/
INC=-I ./src/includes/core
BASELIB=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.4

build:
	g++ -Wall -std=c++17 $(ROOT) $(INC) $(LIB) $(BASELIB) src/*.cpp src/core/*.cpp -o 2DEngine

run:
	./2DEngine
	

clean:
	rm 2DEngine
