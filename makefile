#
#
#

CFLAGS = -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1023 
CFLAGS += -Wfloat-equal -Waggregate-return -Winline

OBJECTS = egg_drop.o egg.o

BIN = egg_drop

$(BIN): $(OBJECTS) egg.h
	gcc $(CFLAGS) $(OBJECTS) -o egg_drop

egg_drop.o: egg_drop.c egg.o
	gcc -c egg_drop.c -o egg_drop.o

egg.o: egg.c egg.h
	gcc -c egg.c -o egg.o

debug: 
	gcc $(CFLAGS) -g $(OBJECTS) -o egg_drop 

profile: 
	gcc $(CFLAGS) -pg $(OBJECTS) -o egg_drop


clean:
	rm -f egg_drop $(OBJECTS)


