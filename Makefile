# Компилятор
CC = g++

# Название игры
GAME = test

# Зависимости
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image

# Debug
DSOURCES = ./Debug/bin/CRSC.cpp  ./Debug/bin/CRSC_lib.cpp

.PHONY: debug
debug:
	$(CC) -lm ./Debug/main.cpp $(DSOURCES) $(LIBS) -o ./Debug/$(GAME)
	./Debug/$(GAME)

.DEFAULT_GOAL := debug