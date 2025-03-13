/* Balaniuc Rodion 315CB */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "command.h"
#include "train.h"

// used for debugging only, set to false in production
bool DEBUG_MODE = false;

void free_queue(CommandQueue *pQueue);

bool is_show(char command[20]) {
    return strcmp(command, "SHOW") == 0;
}

bool is_show_current(char command[20]) {
    return strcmp(command, "SHOW_CURRENT") == 0;
}

bool is_switch(char command[20]) {
    return strcmp(command, "SWITCH") == 0;
}

bool is_execute(char command[20]) {
    return strcmp(command, "EXECUTE") == 0;
}

bool is_move_left(char command[20]) {
    return strcmp(command, "MOVE_LEFT") == 0;
}

bool is_move_right(char command[20]) {
    return strcmp(command, "MOVE_RIGHT") == 0;
}

bool is_write(char command[20]) {
    return strcmp(command, "WRITE") == 0;
}

bool is_clear_cell(char command[20]) {
    return strcmp(command, "CLEAR_CELL") == 0;
}

bool is_clear_all(char command[20]) {
    return strcmp(command, "CLEAR_ALL") == 0;
}

bool is_insert_right(char command[20]) {
    return strcmp(command, "INSERT_RIGHT") == 0;
}

bool is_insert_left(char command[20]) {
    return strcmp(command, "INSERT_LEFT") == 0;
}

bool is_search(char command[20]) {
    return strcmp(command, "SEARCH") == 0;
}

bool is_search_left(char command[20]) {
    return strcmp(command, "SEARCH_LEFT") == 0;
}

bool is_search_right(char command[20]) {
    return strcmp(command, "SEARCH_RIGHT") == 0;
}

bool should_be_queued(char command[20]) {
    if (is_show(command)) {
        return false;
    }
    if (is_show_current(command)) {
        return false;
    }
    if (is_switch(command)) {
        return false;
    }
    if (is_execute(command)) {
        return false;
    }
    return true;
}

void print_train(Train *train) {
    char *text = show(train);
    printf("%s\n", text);
    free(text);
}

void append_line_to_file(char *filename, char *line) {
    //open file for writing
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    fprintf(file, "%s\n", line);
    // close file at the end
    fclose(file);
}

void truncate_file(char *filename) {
    //open file for writing, will erase all content
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    // close file to erase all content without writing anything
    fclose(file);
}

void remove_head(CommandQueue *command_queue) {
    if (command_queue->head == NULL) {
        return;
    }

    Cell *head = command_queue->head;
    Cell *new_head = head->next;
    if (new_head != NULL) {
        new_head->prev = NULL;
    }
    free(head);
    command_queue->head = new_head;
    if (command_queue->head == NULL) {
        command_queue->tail = NULL;
    }
}

int main(int argc, char *argv[]) {
    Train *train = create_train();
    char *output_file = "./tema1.out";
    truncate_file(output_file);

    CommandQueue *queue = read_commands_file("./tema1.in");
    Cell *cursor = queue->head;

    //this is the buffer of queued and not yet executed commands
    CommandQueue *buffer = new_command_queue();

    while (cursor != NULL) {
        Command command = cursor->command;

        if (should_be_queued(command.code)) {
            append(buffer, command);

            if (DEBUG_MODE) {
                printf("[QUEUED] %s %s\n", command.code, command.param);
                printf("\t\t---> ");
                print(buffer, buffer->head, false);
                printf("\n");
            }
        } else if (is_execute(command.code)) {
            if (buffer->head == NULL) {
                printf("ERROR: No commands to execute, skip and move on.\n");
                return 1;
            }

            Command buffer_command = buffer->head->command;
            remove_head(buffer);

            bool operation_succeed = true;
            if (is_move_left(buffer_command.code)) {
                move_left(train);
            } else if (is_move_right(buffer_command.code)) {
                move_right(train);
            } else if (is_write(buffer_command.code)) {
                write(train, buffer_command.param[0]);
            } else if (is_clear_cell(buffer_command.code)) {
                clear_cell(train);
            } else if (is_clear_all(buffer_command.code)) {
                clear_all(train);
            } else if (is_insert_right(buffer_command.code)) {
                insert_right(train, buffer_command.param[0]);
            } else if (is_insert_left(buffer_command.code)) {
                operation_succeed = insert_left(train, buffer_command.param[0]);
            } else if (is_search(buffer_command.code)) {
                operation_succeed = search(train, buffer_command.param);
            } else if (is_search_left(buffer_command.code)) {
                operation_succeed = search_left(train, buffer_command.param);
            } else if (is_search_right(buffer_command.code)) {
                operation_succeed = search_right(train, buffer_command.param);
            }
            if (DEBUG_MODE) {
                printf("++ [RUN] %s: %s %s\n", command.code, buffer_command.code, buffer_command.param);
                printf("\t\t---> ");
                print_train(train);
                if (!operation_succeed) {
                    printf("\t\tout: ERROR\n");
                }
                printf("\t\t---> ");
                print(buffer, buffer->head, false);
                printf("\n");
            }
            if (!operation_succeed) {
                append_line_to_file(output_file, "ERROR");
            }
        } else if (is_show(command.code)) {
            if (DEBUG_MODE) {
                printf("++ [RUN] %s %s\n", command.code, command.param);
                printf("\t\t---> ");
                print_train(train);
                printf("\t\tout: ");
                print_train(train);
            }
            char *line = show(train);
            append_line_to_file(output_file, line);
            free(line);
        } else if (is_show_current(command.code)) {
            char current_char = show_current(train);
            if (DEBUG_MODE) {
                printf("++ [RUN] %s %s\n", command.code, command.param);
                printf("\t\t---> ");
                print_train(train);
                printf("\t\tout: %c\n", current_char);
            }
            char *str = (char *) malloc(2 * sizeof(char));
            str[0] = current_char;
            str[1] = '\0';
            append_line_to_file(output_file, str);
            free(str);
        } else if (is_switch(command.code)) {
            inverse(buffer);
            if (DEBUG_MODE) {
                printf("++ [RUN] %s %s\n", command.code, command.param);
                printf("\t\t---> ");
                print(buffer, buffer->head, false);
                printf("\n");
            }
        } else {
            if (DEBUG_MODE) {
                printf("++ [RUN] %s %s\n", command.code, command.param);
            }
        }
        cursor = cursor->next;
    }

    free_queue(queue);
    free_queue(buffer);

    Wagon *aux, *temp;
    if (train->mechanic != NULL) {
        aux = train->mechanic->next;
        while (aux != train->mechanic) {
            temp = aux;
            aux = aux->next;
            free(temp);
        }
        free(aux);
        train->mechanic = NULL;
        train->sentinel = NULL; 
    }
    free(train);
    return 0;
}

void free_queue(CommandQueue *queue) {
    if (queue->head != NULL) {
        Cell *aux = queue->head;
        while (aux != NULL) {
            Cell *temp = aux;
            aux = aux->next;
            free(temp);
        }
        free(aux);
    }
    free(queue);
}
