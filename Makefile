CC = g++
LANG_STD = -std=c++17
NAME = Engine
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH= -I . \
	      -I ./$(NAME)/libs/ \
	      -I ./$(NAME)/src/includes/core
	      -I ./$(NAME)/src/includes/Entities
	      -I ./$(NAME)/src/includes/GUIPanels
	      -I ./$(NAME)/src/includes/Systems
SRC_FILES = $(NAME)/src/*.cpp \
	    $(NAME)/src/core/*.cpp
	    $(NAME)/src/Entities/*.cpp
	    $(NAME)/src/GUIPanels/*.cpp
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer \
			  -llua5.4
OBJ_NAME = 2DEngine

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o 2DEngine

run:
	./$(OBJ_NAME)
	

clean:
	rm $(OBJ_NAME)
