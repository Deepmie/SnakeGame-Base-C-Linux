#include "board.h"
#include "snake.h"
#include "helper.h"
#define BLOCK "■ "
#define APPLE "\033[31m● \033[0m"

Apple init_apple()
{
    Apple apple;
    apple.n = 0;
    apple.p = NULL;
    return apple;
}

// 初始化一个面板.
Face **init_board(int m, int n)
{
    Face **board = malloc(m * sizeof(Face*));

    for (int i = 0; i < m; i++)
    {
        board[i] = malloc(n * sizeof(Face));

        for (int j = 0; j < n; j++)
        {
            Face face={BLOCK};
            board[i][j] = face;
        }
    }
    return board;
}

// 打印该面板.
void print_board(int m, int n, Face **board)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%s", board[i][j].c);
        }

        printf("\n");
    }
}

bool is_snake_pos(int x, int y, Snake s)
{
    for (int i = 0; i < s.size; i++)
    {
        Position p = s.pos[i];
        if (p.x == x && p.y == y) return true;
    }

    return false;
}

// 随机在面板上生成苹果.
bool generate_apple(int m, int n, Face **board, Snake s, int stand_appnum, Apple *apple)
{
    // 随机挑选除了蛇的位置以外的面板位置作为苹果的位置.
    int total_res_num = (m * n) - s.size;
    int generate_num = stand_appnum - apple->n;
    int rands[generate_num]; // 随机数列表.
    int index = 0, counter = 0;
    if (apple->p == NULL) apple->p = malloc(stand_appnum * sizeof(Position));

    // 生成随机数.
    for (int i = 0; i < generate_num; i++)
    {
        int r;
        while (true) // 确保每次生成的随机数都不相同.
        {
            r = rand() % (total_res_num);
            bool pass = true;
            
            for (int j = 0; j < i; j++)
            {
                if (r == rands[j])
                {
                    pass = false;
                    break;
                }
            }

            if (pass) break;
        }
        rands[i] = r;
    }

    
   if (generate_num > 1) msort(rands, generate_num); // 冒泡法先排一下序.
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (is_snake_pos(i, j, s)) continue;

            if (rands[index] == counter)
            {
                update_board(board, i, j, 'a');
                // printf("i=%d, j=%d\n", i, j);
                Position p = {i, j};
                apple->p[apple->n] = p;
                index ++;
                apple->n ++;

                if (index == generate_num) return true;
            }

            counter ++;
        }
    }

    return true;
}