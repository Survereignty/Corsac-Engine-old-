# Компилятор
CC = g++

# Зависимости
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image

# Debug
Dpath = ./Debug/bin/CRSC/CRSC
DSOURCES =  $(Dpath)_Func.cpp $(Dpath).cpp

.PHONY: debug
debug:
	$(CC) -lm ./Debug/main.cpp -fPIC -m64 $(DSOURCES) $(LIBS) -o ./Debug/CorsacGame
	./Debug/CorsacGame

# Release
Rpath = ./Release/bin/CRSC/CRSC
RSOURCES = $(Rpath).so $(Rpath)_Func.so
.PHONY: release
release:
	cp ./Debug/main.cpp ./Release

	cp $(Dpath)_Func.h ./Release/bin/CRSC
	$(CC) --shared -fPIC $(Dpath)_Func.cpp -o $(Rpath)_Func.so
	cp $(Dpath).h ./Release/bin/CRSC
	$(CC) --shared -fPIC $(Dpath).cpp -o $(Rpath).so

	$(CC) -lm ./Release/main.cpp -fPIC -m64 $(RSOURCES) $(LIBS) -o ./Release/CorsacGame

	rm $(Rpath)_Func.h
	rm $(Rpath).h

	rm ./Release/main.cpp

	./Release/CorsacGame

.DEFAULT_GOAL := debug