# Balaniuc Rodion 315CB 

CFLAGS=-Wall -Werror

build:
	gcc command.h train.h command.c train.c main.c $(CFLAGS) -o ./tema1

run: compile
	./tema1

clean:
	rm -f tema1

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema1
