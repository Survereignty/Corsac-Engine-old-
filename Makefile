# Компилятор
CC = g++

# Зависимости
SOURCES = -lSDL2main -lSDL2 -lSDL2_mixer -lGL -lglut

# build and start
.PHONY: run
run:
	$(CC) -lm -m64 -o engine ./bin/core/main.cpp $(SOURCES)
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