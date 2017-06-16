#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_num_array(int * c)
{
    int index = 0;
    for(; c[index] == 0; ++index);
    //printf("INDEX: %d\n", index);
    for(index; index < 512; ++index)
    {
        printf("%d", c[index]);
    }
    puts("");
}

int * adder(int * a, int * b, int * c)
{
    //TODO: Figure out how to handle carry properly.
    //puts("adder~");
    int carry = 0;
    int sum = 0;
    int start = 512 - 1;
    for(int i = start; i > 0; i--)
    {
        sum = (a[i] + b[i] + carry);
        c[i] = sum % 10;
        carry = sum / 10;
        --start;
    }

    return c;
}

void fibo(int fibno, int * a, int * b, int * c)
{

    a[511] = 1;
    b[511] = 1;
    fibno = fibno - 2;

    while(fibno > 0)
    {
        c = adder(a, b, c);
        //printf("line~\n");
        print_num_array(c);
        //puts("~line");
        memcpy(a, b, 512 * sizeof(int));
        memcpy(b, c, 512 * sizeof(int));
        //print_num_array(c);
        //printf("first: %d\n", c[511]);
        //memset(c, 0, 512 * sizeof(int));
        //printf("first: %d\n", c[511]);
        --fibno;
    }
}

void make_array(char * string, int * num, int start)
{
    int end = strlen(string);
    printf("end: %d\n", end);
    for(int i = end - 1; string[i] != '\0'; --i)
    {
        if(isdigit(string[i]))
        {
            num[start] = string[i] - '0';
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

    //make_array(test, a, start);
    //make_array("300", b, start);
    fibo(300, a, b, c);

    int index = 0;
    for(; c[index] == 0; ++index);
    printf("INDEX: %d\n", index);
    for(index; index < 512; ++index)
    {
        printf("%d", c[index]);
    }
    puts("");

}






















