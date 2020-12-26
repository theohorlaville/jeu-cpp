
CC=g++
CFLAGS= -Wall

play: main.o jeu.o affichage.o
	$(CC) -o $@ $^ -I include -L lib -l SDL2-2.0.0 -l SDL2_Image -l SDL2_TTF $(CFLAGS)

main.o: main.cpp struct.h jeu.h
	$(CC) -o $@ -c $< 

affichage.o: affichage.cpp struct.h
	$(CC) -o $@ -c $<

jeu.o: jeu.cpp struct.h jeu.h
	$(CC) -o $@ -c $<


clean:
	rm -rf *.o