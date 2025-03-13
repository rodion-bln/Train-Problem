/* Balaniuc Rodion 315CB */

#ifndef COMMAND_H
#define COMMAND_H 1

#include <stdbool.h>

typedef struct Command {
    char code[20];
    char param[80];
} Command;

typedef struct Cell {
    Command command;
    struct Cell* next;
    struct Cell* prev;
} Cell;

typedef struct CommandQueue {
    Cell* head;
    Cell* tail;
} CommandQueue;

CommandQueue* read_commands_file(char *filename);

void print(CommandQueue* queue, Cell* cursor, bool multiline);

// Switch direction of commands in queue
void inverse(CommandQueue* commandQueue);

CommandQueue* new_command_queue();

void append(CommandQueue *queue, Command command);

#endif