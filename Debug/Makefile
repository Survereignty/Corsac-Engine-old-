# Компилятор
CC = g++

# Зависимости
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image

# Debug
DSOURCES = ./bin/CRSC.cpp  ./bin/CRSC_lib.cpp

.PHONY: debug
debug:
	$(CC) -lm ./main.cpp $(DSOURCES) $(LIBS) -o ./SkyFort
	./SkyFort

.DEFAULT_GOAL := debug