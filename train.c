/* Balaniuc Rodion 315CB */

#include "train.h"
#include <malloc.h>

Wagon *create_wagon() {
    Wagon *wagon = (Wagon *) malloc(sizeof(Wagon));
    wagon->next = NULL;
    wagon->prev = NULL;
    wagon->val = '#';
    return wagon;
}

Train *create_train() {
    Wagon *first_wagon = create_wagon();
    Train *train = (Train *) malloc(sizeof(Train));

    train->sentinel = (Wagon *) malloc(sizeof(Wagon));

    train->sentinel->next = first_wagon;
    train->sentinel->prev = first_wagon;
    first_wagon->prev = train->sentinel;
    first_wagon->next = train->sentinel;

    train->mechanic = first_wagon;

    return train;
}

char show_current(Train *train) {
    return train->mechanic->val;
}

char *show(Train *train) {
    int i = 0;
    char *result = (char *) malloc(1000);

    Wagon *current = train->sentinel->next;
    while (current != train->sentinel) {
        if (current == train->mechanic) {
            result[i++] = '|';
            result[i++] = current->val;
            result[i++] = '|';
        } else {
            result[i++] = current->val;
        }
        current = current->next;
    }
    result[i] = '\0';
    return result;
}

void write(Train *train, char val) {
    train->mechanic->val = val;
}

void move_left(Train *train) {
    train->mechanic = train->mechanic->prev;
    if (train->mechanic == train->sentinel) {
        train->mechanic = train->mechanic->prev;
    }
}

void move_right(Train *train) {
    if (train->mechanic->next == train->sentinel) {
        insert_right(train, '#');
    } else {
        train->mechanic = train->mechanic->next;
    }
}

void clear_cell(Train *train) {
    Wagon *wagon = train->mechanic;
    if (wagon->next != train->sentinel || wagon->prev != train->sentinel) {
        Wagon *prev = wagon->prev;
        Wagon *next = wagon->next;

        move_left(train);

        prev->next = wagon->next;
        next->prev = wagon->prev;
        free(wagon);
    } else {
        write(train, '#');
    }
}

void clear_all(Train *train) {
    while (train->mechanic->next != train->sentinel || train->mechanic->prev != train->sentinel) {
        clear_cell(train);
    }
    write(train, '#');
}

void insert_right(Train *train, char val) {  
    Wagon *wagon = create_wagon();
    wagon->val = val;
    Wagon *mechanic = train->mechanic;

    wagon->next = mechanic->next;   
    wagon->prev = mechanic;        

    wagon->next->prev = wagon; 
    
    mechanic->next = wagon;

    // move mechanic to the new wagon
    train->mechanic = wagon;
}

bool insert_left(Train *train, char val) {
    Wagon *mechanic = train->mechanic;
    if(mechanic->prev == train->sentinel) {
        return false;
    }
    Wagon *wagon = create_wagon();
    wagon->val = val;

    wagon->prev = mechanic->prev;
    wagon->next = mechanic;

        wagon->prev->next = wagon;

    mechanic->prev = wagon;

    //move mechanic to the new wagon
    train->mechanic = wagon;

    return true;
}

bool search(Train *train, char *text) {
    Wagon *start = train->mechanic;
    Wagon *sentinel = train->sentinel;
    // iterate between a whole loop between mechanic and its reoccurrence.
    // we search to the right
    do {
       
        int i = 0;
        Wagon *current = start;

        // iterate from current wagon to the right until the text is found or mechanic reached
        while (text[i] != '\0' && text[i] == current->val ) {
            current = current->next;
            // skip sentinel when encountered
            if (current == sentinel) {
                current = current->next;
            }
            i++;
        }

        // all characters where found and terminal character is reached
        // this means that the text is found
        if (text[i] == '\0') {
            // mechanic is set to FIRST character of the text
            train->mechanic = start;
            // for edge case prev pointer is sentinel
            return true;
        }
        start = start->next;
         //skip sentinel when encountered
        if (start == sentinel) {
            start = start->next;
        }
    } while (start != train->mechanic);
    return false;
}

bool search_right(Train *train, char *text) {
    Wagon *start = train->mechanic;
    Wagon *sentinel = train->sentinel;
    // iterate between mechanic and sentinel only as we search to the right
    while (start != sentinel) {
        int i = 0;
        Wagon *current = start;

        // iterate from current wagon to the right until the text is found or sentinel reached
        while (text[i] != '\0' && (text[i] == current->val && current != sentinel)) {
            current = current->next;
            i++;
        }

        // all characters where found and terminal character is reached
        // this means that the text is found
        if (text[i] == '\0') {
            // mechanic is set to LAST character of the text
            train->mechanic = current->prev;
            return true;
        }
        start = start->next;
    }
    return false;
}

bool search_left(Train *train, char *text) {
    Wagon *start = train->mechanic;
    Wagon *sentinel = train->sentinel;
    // iterate between mechanic and sentinel only as we search to the right
    while (start != sentinel) {
        int i = 0;
        Wagon *current = start;

        // iterate from current wagon to the left until the text is found or sentinel reached
        while (text[i] != '\0' && (text[i] == current->val && current != sentinel)) {
            current = current->prev;
            i++;
        }

        // all characters where found and terminal character is reached
        // this means that the text is found
        if (text[i] == '\0') {
            // mechanic is set to LAST character of the text
            train->mechanic = current->next;
            return true;
        }
        start = start->prev;
    }
    return false;
}
