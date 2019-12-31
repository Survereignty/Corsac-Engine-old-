# Компилятор
CC = g++

# Зависимости
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

# Debug
DSOURCES = ./bin/CRSC.cpp  ./bin/CRSC_lib.cpp

.PHONY: debug
debug:
	$(CC) -lm ./main.cpp $(DSOURCES) $(LIBS) -o ./TestGame
	./TestGame

.DEFAULT_GOAL := debug