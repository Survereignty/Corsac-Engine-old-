.PHONY: run
run:
	g++ -lm -o engine ./bin/core/main.cpp -lSDL2main -lSDL2 -lGL -lGLEW -lSDL2_mixer
	./engine

.DEFAULT_GOAL := run