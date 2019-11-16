# Компилятор
CC = g++

# Зависимости
SOURCES = -lSDL2main -lSDL2 -lGL -lGLEW -lSDL2_mixer

# build and start
.PHONY: run
run:
	$(CC) -lm -o engine ./bin/core/main.cpp $(SOURCES)
	./engine

# build
.PHONY: build
build:
	$(CC) -lm -o engine ./bin/core/main.cpp $(SOURCES)

# start
.PHONY: start
start:
	./engine

.DEFAULT_GOAL := run