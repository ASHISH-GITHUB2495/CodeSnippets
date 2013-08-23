//#include <stdlib.h>
#include <iostream>

typedef struct _stack_item
{
    int index;
    int value;
}stack_item;

typedef long long int_64;

int H[100000];


void area(int n)
{
    stack_item *stack = new stack_item[n];
    int top  = -1;
    int left;

    int_64 now_area, max_area = 0;

    for(int i = 0; i <= n; i++)
    {
        while(top >= 0 && ( i == n || stack[top].value > H[i] ))
        {
            if( top == 0 )
            {
                left = -1;
            }
            else 
            {
                left = stack[top-1].index;
            }

            now_area = (int_64)(i-left-1)*stack[top].value;
            top--;

            if(now_area > max_area) max_area = now_area;

        }
        if( i < n )
        {
            top++;
            stack[top].value = H[i];
            stack[top].index = i;
        }

    }
    printf("%lld\n", max_area);
    delete stack;
    //return max_area;

}

int main()
{
    int i, n;
    int_64 max_area;

    while(scanf("%d", &n) != EOF && n)
    {
        for(i = 0; i < n; i++)
        {
            scanf("%d", &H[i]);
        }
        area(n);
        //printf("%lld\n", max_area);
    }

    return 0;
}
