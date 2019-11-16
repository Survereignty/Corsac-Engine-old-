.PHONY: run
run:
	g++ -lm -o engine ./bin/core/main.cpp -lSDL2main -lSDL2 -lGL -lGLEW
	./engine

.DEFAULT_GOAL := run