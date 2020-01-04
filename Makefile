# Компилятор
CC = g++

# Название игры
GAME = CG

# Зависимости
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

# /////////////////////// Debug /////////////////////////
DebugSOURCES = ./Debug/bin/CRSC/CRSC.cpp ./Debug/bin/CRSC/CRSC_db.cpp #./Debug/bin/Rily/AddObject.cpp ./Debug/bin/Rily/DrawObject.cpp ./Debug/bin/Rily/Events.cpp ./Debug/bin/Rily/rect.cpp ./Debug/bin/Rily/rect_Move.cpp ./Debug/bin/Rily/rily.cpp ./Debug/bin/Rily/tringle.cpp ./Debug/bin/Rily/tringle_Move.cpp

.PHONY: debug
debug:
	$(CC) -lm ./Debug/CG.cpp $(DebugSOURCES) $(LIBS) -o ./Debug/$(GAME)
	./Debug/$(GAME)

# /////////////////////// Dist /////////////////////////
DistSOURCES = ./Dist/bin/CRSC/CRSC.so ./Dist/bin/CRSC/CRSC_db.cpp

.PHONY: builddist
builddist:
	rm -rf ./Dist
	mkdir Dist
	cp -r ./Debug/bin/CRSC ./Dist
	cp ./Debug/CG.cpp ./Dist

	$(CC) -fpic -c ./Dist/bin/CRSC/CRSC.cpp -o ./Dist/bin/CRSC/CRSC.so
	rm ./Dist/bin/CRSC/CRSC.cpp

	$(CC) -lm ./Dist/CG.cpp $(DistSOURCES) $(LIBS) -o ./Dist/$(GAME)

.PHONY: dist
dist:
	$(CC) -lm ./Dist/CG.cpp $(DistSOURCES) $(LIBS) -o ./Dist/$(GAME)
	./Dist/$(GAME)

# /////////////////////// Release /////////////////////////

.DEFAULT_GOAL := debug