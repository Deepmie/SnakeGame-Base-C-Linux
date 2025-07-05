## 这是一个基于C语言的贪吃蛇程序

> 我的第一个C语言项目。

笔者想要入门嵌入式开放，通过阅读了另一个windows平台的贪吃蛇代码，大致学会了指针、结构体等C语言特色的代码，因此在Linux上面搭建了一个类似的程序，实现了贪吃蛇小游戏的基本逻辑。

由于时间紧迫，没有做游戏结束画面，同时可能还有一些bug没有测试出来。你可以通过修改main.c中的一些内容来让这个游戏的一些参数发生改变，例如蛇的初始位置和长度、苹果的数量、游戏的速度等等关键参数。

该项目非常基础，只是笔者用于记录的一个仓库。

贪吃蛇游戏的实际界面:

<img src="src/demo.gif" alt="演示动画" width="200">

您可以键入'q'键开始游戏，对应main.c的这部分代码:
```c
if (c == 'q')
{
    game = true;
    printf("Game Start!\n");
    generate_apple(m, n, board, s, stand_appnum, &apple);
    usleep(1000000);
    system("clear");
}
```

初始默认有一条红色的长度为三的蛇，局中有三个苹果，对应main.c的这部分代码：
```c
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
```

您可以调整参数以修改这些值以获得更好的游戏体验。希望能帮助到同为C语言项目的初学者。