#ifndef HELPER_H
#define HELPER_H

typedef struct{
    int x;
    int y;
} Position;

typedef struct{
    char d;
    int size;
    Position *pos;
} Snake;

typedef struct
{
    char *c;
} Face;

typedef struct
{
    int n;
    Position *p;
} Apple;

// 冒泡法排序.
void msort(int *arr, int n);

#endif