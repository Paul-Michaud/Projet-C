projet:fonction.o main.o fonction_sdl.o
	gcc fonction.o main.o fonction_sdl.o -o projet -Wall -lSDL -lSDL_mixer -lSDL_ttf


fonction.o:fonction.c fonction.h fonction.h
	gcc -c fonction.c -Wall -lSDL -lSDL_mixer -lSDL_ttf

fonction_sdl.o:fonction_sdl.c fonction_sdl.h fonction.h
	gcc -c fonction_sdl.c -Wall -lSDL -lSDL_mixer -lSDL_ttf


main.o:main.c fonction.h fonction_sdl.h
	gcc -c main.c -Wall -lSDL -lSDL_mixer -lSDL_ttf

clean:
	rm *.o projet

