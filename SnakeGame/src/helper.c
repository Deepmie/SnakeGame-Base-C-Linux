#include "helper.h"

void msort(int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n-i; j ++)
        {
            int curr = arr[j], next = arr[j+1];
            if (curr > next) {arr[j+1] = curr; arr[j] = next;} // 交换前后元素.
        }
    }
}