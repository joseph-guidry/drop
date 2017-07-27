#
#
#

egg_drop: egg_drop.o egg.o egg.h
	gcc -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -o egg_drop egg_drop.c 

egg.o: egg.c egg.h
	gcc -c egg.c -o egg.o

#debug:

#profile:

clean:
	rm egg_drop *.o


