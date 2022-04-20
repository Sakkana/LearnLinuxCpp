#include <stdio.h>
#include "head.h"

int main()
{
    int a = 9, b = 7;
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", sub(a, b));
    printf("a + b = %d\n", multi(a, b));
    printf("a * b = %lf\n", div((double)a, (double)b));
    return 0;
}
