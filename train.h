/* Balaniuc Rodion 315CB */

#include <stdbool.h>
#include "command.h"


#ifndef TRAIN_H
#define TRAIN_H 1
typedef struct Wagon {
    char val;
    struct Wagon* next;
    struct Wagon* prev;
} Wagon;

typedef struct Train {
    Wagon* sentinel;
    Wagon* mechanic;
} Train;

// Creates a train with a sentinel, one wagon and a mechanic tracking first wagon
Train* create_train();

// Moves mechanic to the left wagon.
// If there is no left wagon, mechanic circles to last wagon.
void move_left(Train* train);

// Shifts the mechanic one wagon to the right.
// If no wagon exists to the right, a new one is created to the right and the mechanic is moved there.
void move_right(Train* train);

// Writes a character to the wagon where the mechanic is.
void write(Train* train, char val);

// Deletes the wagon where the mechanic is.
// Mechanic moves to the left wagon.
// If there is no left wagon, mechanic moves to last wagon.
void clear_cell(Train* train);

// Deletes all wagons.
void clear_all(Train* train);

// Inserts a new wagon to the left of the mechanic.
// If mechanic is at the first wagon, ERROR message is printed.
bool insert_left(Train* train, char val);

// Inserts a new wagon to the right of the mechanic.
void insert_right(Train* train, char val);

// Searches for a text in the train in circular manner.
bool search(Train* train, char* text);

// Searches for a text in the train in left direction.
bool search_left(Train* train, char* text);

// Searches for a text in the train in right direction.
bool search_right(Train* train, char* text);

// Shows the value for current position of the mechanic.
char show_current(Train* train);

// Shows the train starting from the first wagon.
char* show(Train* train);

// Execute first command from buffer
void execute(Train* train, CommandQueue* buffer);

#endif