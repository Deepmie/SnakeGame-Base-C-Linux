#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "terminal.h"

void change_terminal_mode(bool mode) // 修改终端响应模式.
{
    static struct termios oldt, newt;
    if (mode)
    {
        tcgetattr(STDIN_FILENO, &oldt); // 记录当前终端设置
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // 关闭缓冲和回显
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // 设置非阻塞读取
    }
    else
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 恢复设置
        fcntl(STDIN_FILENO, F_SETFL, 0); // 取消非阻塞
    }
}