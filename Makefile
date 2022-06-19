CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH= -I . \
			  -I ./libs/ \
			  -I ./src/includes/core
SRC_FILES = src/*.cpp \
			src/core/*.cpp
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer \
			  -llua5.4
OBJ_NAME = 2DEngine

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o 2DEngine

run:
	./$(OBJ_NAME)
	

clean:
	rm $(OBJ_NAME)
