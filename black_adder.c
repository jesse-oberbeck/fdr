#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/bn.h>

void print_num_array(int * c)
{
    int index = 0;
    for(; c[index] == 0; ++index);
    for(; index < 512; ++index)
    {
        printf("%d", c[index]);
    }
    puts("");
}

char * stringify(int * ints, char * string)
{
    int index = 0;
    for(; ints[index] == 0; ++index);
    for(; index < 512; ++index)
    {
        sprintf(string, "%s%d", string, ints[index]);
    }
    puts("");
    return(string);
}

char * to_hex(char * string)
{
    BIGNUM * big_num = BN_new();
    BN_dec2bn(&big_num, string);
    return(BN_bn2hex(big_num));
}

int roman(char * string)
{
    int accumulator = 0;
    char characters[7] = "MDCLXVI";
    int vals[7] = {1000, 500, 100, 50, 10, 5, 1};
    int occurences[7] = {0};
    int prev_val = 1000;
    int new_val = 0;

    for(unsigned int i = 0; i < strlen(string); ++i)
    {
        for(unsigned int j = 0; j < 7; ++j)
        {

            if(string[i] == characters[j])
            {

                new_val = vals[j];
                occurences[j] = occurences[j] + 1;
                if(new_val > prev_val)
                {
                    return(0);
                }

                if(occurences[j] > 4)
                {
                    return(0);
                }

                else
                {
                    accumulator = accumulator + new_val;
                }

            }
        }
    }
    return(accumulator);
}

int * adder(int * a, int * b, int * c)
{
    //TODO: Figure out how to handle carry properly.
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

        //print_num_array(c);

        memcpy(a, b, 512 * sizeof(int));
        memcpy(b, c, 512 * sizeof(int));

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
    //char * test = "779";
    int a[512] = {0};
    int b[512] = {0};
    int c[512] = {0};
    char string[512] = {'\0'};

    int start = 512 - 1;

    //make_array(test, a, start);
    //make_array("300", b, start);
    fibo(300, a, b, c);

    printf("roman: %d\n", roman("MMMMCVIIII"));
    stringify(c, string);
    printf("stringify: %s\n", string);
    char * bign = to_hex(string);
    printf("bignum hex: %s\n", bign);
    printf("fibo: ");
    print_num_array(c);


}






















