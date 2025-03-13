/* Balaniuc Rodion 315CB */

#include <stddef.h>
#include "command.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

bool should_have_param(char command[20]);

CommandQueue* new_command_queue() {
    CommandQueue* commandQueue = (CommandQueue*)malloc(sizeof(CommandQueue));
    commandQueue->head = NULL;
    commandQueue->tail = NULL;

    return commandQueue;
}

// Switch direction of commands in queue
// not naming function "switch" as it is a reserved keyword in C
void inverse(CommandQueue* commandQueue) {
    Cell *head = commandQueue->head;
    Cell *tail = commandQueue->tail;

    Cell *current = head;
    while (current != NULL) {
        Cell *temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }

    commandQueue->head = tail;
    commandQueue->tail = head;
}

void append(CommandQueue *queue, Command command) {
    Cell *cell = (Cell *) malloc(sizeof(Cell));
    cell->command = command;
    cell->prev = NULL;
    cell->next = NULL;
    if (queue->head == NULL) {
        //when queue is empty we need to set the head and tail to the new cell
        queue->head = cell;
        queue->tail = cell;
    } else {
        bool has_one_element = queue->head == queue->tail;
        if (has_one_element) {
            //when queue has only one element we need to update the head next and tail
            //link the new cell to the head
            queue->head->next = cell;
            cell->prev = queue->head;
            //update the tail
            queue->tail = cell;
            return;
        } else {
            //when queue is not empty we need to append the new cell and update the tail
            //link the new cell to current tail
            queue->tail->next = cell;
            cell->prev = queue->tail;
            //update the tail
            queue->tail = cell;
        }
    }
}

void print(CommandQueue* queue, Cell* cursor, bool multiline) {
    Cell *current = queue->head;
    while (current != NULL) {
        char *command = current->command.code;
        char *param = current->command.param;
        if (multiline) {
            if(cursor == current) {
                printf("|%s %s|\n", command, param);
            } else {
                printf("%s %s\n", command, param);
            }
        } else {
            if(cursor == current) {
                printf("|%s %s|, ", command, param);
            } else {
                printf("%s %s, ", command, param);
            }
        }
        current = current->next;
    }
}

CommandQueue* read_commands_file(char *filename) {
    CommandQueue* commandQueue = new_command_queue();

    //open file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return commandQueue;
    }

    int commands;
    fscanf(file, "%d", &commands);
    int i = 0;
    for ( ; i < commands; i++) {
        Command command;
        fscanf(file, "%s", command.code);

        if (should_have_param(command.code)) {
            fscanf(file, "%s", command.param);
        } else {
            command.param[0] = '\0';
        }
        append(commandQueue, command);
    }

    // close file at the end
    fclose(file);
    return commandQueue;
}

bool should_have_param(char command[20]) {
    if (strcmp(command, "WRITE") == 0) {
        return true;
    }
    if (strcmp(command, "INSERT_RIGHT") == 0) {
        return true;
    }
    if (strcmp(command, "INSERT_LEFT") == 0) {
        return true;
    }
    if (strcmp(command, "SEARCH") == 0) {
        return true;
    }
    if (strcmp(command, "SEARCH_RIGHT") == 0) {
        return true;
    }
    if (strcmp(command, "SEARCH_LEFT") == 0) {
        return true;
    }
    return false;
}
