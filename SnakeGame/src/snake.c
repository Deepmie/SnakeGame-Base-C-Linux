#include "snake.h"
#include "board.h"
#define SNAKE_BLOCK "\033[31m■ \033[0m"
#define BLOCK "■ "
#define APPLE "\033[31m● \033[0m"

void update_board(Face **board, int i, int j, char mode)
{
    if (mode == 's') board[i][j].c = SNAKE_BLOCK; else if (mode == 'b') board[i][j].c = BLOCK; else if (mode == 'a') board[i][j].c = APPLE;
}

bool update_snake_direction(Snake *s, char c)
{
    // 确保c输入的是四个选项.
    if (c != 'w' && c != 's' && c != 'd' && c != 'a')
    {
        return false; // 没有修改方向.
    }

    // 确保c不能让蛇回头.
    if (s->size > 1)
    {
        Position *s_p = s->pos;
        Position head = s_p[0];
        Position head_next = s_p[1];

        if (head_next.y == head.y && head_next.x == head.x - 1 && c == 'w')
        {
            // 不能往上走.
            return false;
        }
        else if (head_next.y == head.y && head_next.x == head.x + 1 && c == 's')
        {
            // 不能往下走.
            return false;
        }
        else if (head_next.y == head.y - 1 && head_next.x == head.x && c == 'a')
        {
            // 不能往左走.
            return false;
        }
        else if (head_next.y == head.y + 1 && head_next.x == head.x && c == 'd')
        {
            // 不能往右走.
            return false;
        }
        else
        {
            // 全部条件满足.
            s->d = c;
            return true;
        }
    }

    else
    {
        s->d = c;
        return true;
    }
}

Snake init_snake(char d, int size, Position *pos, Face **board)
{
    Snake s;
    s.pos = pos;
    s.d = d;
    s.size = size;
    for (int i = 0; i < size; i++) update_board(board, pos[i].x, pos[i].y, 's');
    return s;
}

bool is_apple_position(Position head, Apple *apple)
{
    // printf(" head: x=%d, y=%d\n", head.x, head.y);
    for (int i = 0; i < apple->n; i ++)
    {
        Position apple_pos = apple->p[i];
        // printf("apple: x=%d, y=%d\n", apple_pos.x, apple_pos.y);

        if (apple_pos.x == head.x && apple_pos.y == head.y)
        {
            Position *temp = malloc((apple->n - 1) * sizeof(Position));
            int l = 0;
            for (int j = 0; j < apple->n; j ++)
            {
                if (j != i) {temp[l] = apple->p[j]; l++;}
            }
            apple->p = temp;
            apple->n --;
            return true;
        }
    }
    return false;
}

bool is_die(Position head, int m, int n, Snake s)
{
    if (head.x < 0 || head.y < 0 || head.x > m - 1 || head.y > n - 1) return true; // 碰不碰边界.
    
    for (int i=1; i < s.size; i++) // 检查是否碰到身体部分.
    {
        Position spos = s.pos[i];
        if (head.x == spos.x && head.y == spos.y) return true;
    }

    return false;
}

bool update_head(char d, Position *head, int m, int n, Snake *s, Apple *apple, IsEatApp *isl, int stand_appnum, Face **board)
{
    switch (d)
    {
        case 'w':
            head->x -= 1;
            break;

        case 'a':
            head->y -= 1;
            break;

        case 's':
            head->x += 1;
            break;
        
        case 'd':
            head->y += 1;
            break;
    }

    // 每次更新头部的时候都要考虑是否会触发和头部相关的事件.
    if (is_die(*head, m, n, *s)) return false; // 检查是否死了.


    // 检查是否吃到了苹果.
    if (is_apple_position(*head, apple))
    {
        // 下一帧的时候加长它.
        // printf("eat..\n");
        bool value = true;
        isl->next = &value;
        generate_apple(m, n, board, *s, stand_appnum, apple);
    }
    
    return true;
}

bool update_snake(Snake *s, int m, int n, Face **board, Apple *apple, int stand_appnum)
{
    static IsEatApp isl;
    Position *head = &s->pos[0];
    Position tail = s->pos[s->size-1];

    // 更新非头节点.
    for (int i = s->size-1; i > 0; i--)
    {
        Position *now_pos = &s->pos[i];
        *now_pos = s->pos[i-1];
    }

    update_board(board, tail.x, tail.y, 'b');

    bool res = update_head(s->d, head, m, n, s, apple, &isl, stand_appnum, board);
    if (!res) return false;
    // if (is_die(*head, m, n, *s)) return false; // check.

    // 更新板和蛇的状态.
    update_board(board, head->x, head->y, 's');

    // printf("tail: x=%d, y=%d\n", tail.x, tail.y);

    if (isl.curr != NULL && *isl.curr)
    {
        // 更新蛇的状态.
        Position *temp = malloc((s->size+1) * sizeof(Position));
        for (int i = 1; i < s->size + 1; i++) temp[i] = s->pos[i-1];

        bool res = update_head(s->d, head, m, n, s, apple, &isl, stand_appnum, board);
        if (!res) return false;

        // if (is_die(*head, m, n, *s)) return false; // check.
        update_board(board, head->x, head->y, 's');

        temp[0] = *head;

        free(s->pos);
        s->pos = temp;
        s->size ++;
    }

    // 更新指示类.

    if (isl.next != NULL)
    {
        bool value = *isl.next;
        isl.curr = &value;
    }
    else
    {
        isl.curr = NULL;
    }
    isl.next = NULL;
    
    // printf("snake: x=%d, y=%d\n", head->x, head->y);
    // printf("apples:\nnum=%d\n", apple->n);
    // for (int i = 0; i < apple->n; i ++) printf("x=%d, y=%d\n", apple->p[i].x, apple->p[i].y);
    return true;
}