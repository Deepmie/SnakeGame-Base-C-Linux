#ifndef BOARD_H
#define BOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper.h"

Apple init_apple();
Face **init_board(int m, int n);
void print_board(int m, int n, Face **board);
bool generate_apple(int m, int n, Face **board, Snake s, int stand_appnum, Apple *apple);

#endif