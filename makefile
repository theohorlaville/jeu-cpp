
CC=g++
CFLAGS= -Wall
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

play: main.o jeu.o affichage.o
	$(CC) -o $@ $^ $(LINKER_FLAGS) $(CFLAGS)



affichage.o: affichage.cpp struct.h 
	$(CC) -o $@ -c $<

main.o: main.cpp struct.h jeu.h  affichage.h
	$(CC) -o $@ -c $<

jeu.o: jeu.cpp struct.h jeu.h
	$(CC) -o $@ -c $<

clean:
	rm -rf *.o