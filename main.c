#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "board.h"
#include "snake.h"
#include "terminal.h"

void main(){
    srand(time(NULL)); // 设定随机种子.
    Face **board;
    Snake s;
    Apple apple;
    int m = 10, n = 10; // 初始地图大小
    int size = 3; // 初始长度.
    char d = 'w'; // 初始方向.
    int stand_appnum = 3; // 标准的苹果数量.

    Position p1 = {m-3, n-1};
    Position p2 = {m-2, n-1};
    Position p3 = {m-1, n-1};
    Position *p = malloc(3 * sizeof(Position)); // 蛇的初始位置.
    p[0] = p1; p[1] = p2; p[2] = p3;

    bool game = false;
    // bool game = true;

    board = init_board(m, n);
    s = init_snake(d, size, p, board);
    apple = init_apple();
    print_board(m, n, board);

    change_terminal_mode(true);

    while (true)
    {
        char c;
        ssize_t nt = read(STDIN_FILENO, &c, 1);

        if (nt > 0)
        {
            if (c == 'q')
            {
                game = true;
                printf("Game Start!\n");
                generate_apple(m, n, board, s, stand_appnum, &apple);
                usleep(1000000);
                system("clear");
            }
            
            // if (c == 'w' || c == 's' || c == 'd' || c == 'a') s.d = c;
            update_snake_direction(&s, c);
        }

        
        if (game)
        {
            system("clear");
            // printf("-----\n");
            bool result = update_snake(&s, m, n, board, &apple, stand_appnum);
            if (result==false) break;
            print_board(m, n, board);
        }

        usleep(500000);
    }
    change_terminal_mode(false);

}
