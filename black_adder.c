#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int * adder(int * a, int * b, int * c)
{
    //TODO: Figure out how to handle carry properly.
    int carry = 0;
    int sum = 0;
    int start = 512 - 1;
    for(int i = start; i > 500; i--)
    {
        sum = (a[i] + b[i]) % 10;
        printf("sum: %d + %d = %d\n",a[i], b[i], sum);
        c[start] = sum + carry;
        carry = 0;
        carry = (a[i] + b[i]) / 10;
        printf("~~carry: %d\n", carry);
        printf("summed: %d\n",c[start]);
        --start;
    }
    return c;
}

void make_array(char * string, int * num, int start)
{
    int end = strlen(string);
    printf("end: %d\n", end);
    for(int i = end - 1; string[i] != '\0'; --i)
    {
        if(isdigit(string[i]))
        {
            //printf("c:%c\n", string[i]);
            num[start] = string[i] - '0';
            //printf("d:%d\n", num[start]);
            --start;
        }
    }
}

int main(void)
{
    char * test = "779";
    int a[512] = {0};
    int b[512] = {0};
    int c[512] = {0};

    int start = 512 - 1;
    //a[start] = 5;
    //a[start - 1] = 4;


    make_array(test, a, start);
    make_array("300", b, start);
    adder(a, b, c);

    //printf("start: %d\n", start);
    for(int i = start; i > 500; i--)
    {
        printf("%d",c[i]);
    }
    puts("");
}
