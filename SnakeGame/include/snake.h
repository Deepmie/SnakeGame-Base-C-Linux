#ifndef SNAKE_H
#define SNAKE_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helper.h"

typedef struct
{
    bool *curr;
    bool *next;
} IsEatApp;

void update_board(Face **board, int i, int j, char mode);
bool update_snake_direction(Snake *s, char c);
Snake init_snake(char d, int size, Position *pos, Face **board);
bool update_snake(Snake *s, int m, int n, Face **board, Apple *apple, int stand_appnum);

#endif