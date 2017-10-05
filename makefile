CC=gcc
CFLAGS=-lm
DEPS = brut_input.h serial.h traitement.h
OBJ = laser.o brut_input.o serial.c traitement.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hokuyo: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
