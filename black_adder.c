#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/bn.h>

void print_num_array(int * c)
{
    //Prints an array of integers.
    int index = 0;
    for(; c[index] == 0; ++index);
    for(; index < 128; ++index)
    {
        printf("%d", c[index]);
    }
    puts("");
}

char * stringify(int * ints, char * string)
{
    //Turns an array into a single string.
    int index = 0;
    for(; ints[index] == 0; ++index);
    for(; index < 128; ++index)
    {
        sprintf(string, "%s%d", string, ints[index]);
    }
    return(string);
}

char * to_hex(char * string)
{
    //Uses the bignum library (discovered via Liam by way of Ems.)
    //to convert very large numbers to a string of their hex representation.
    BIGNUM * big_num = BN_new();
    BN_dec2bn(&big_num, string);
    return(BN_bn2hex(big_num));
}

char * roman(char * string)
{
    //Translates a recieved string of Roman numerals into decimal.
    //Letters which have no Roman value are simply passed over and ignored.
    //All valid Roman numerals are added to the accumulator.
    //Roman numerals must be in the older, additive style.
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
    char * rom_num = calloc(16, 1);
    snprintf(rom_num, 15, "%d%c", accumulator, '\0');
    rom_num[16] = '\0';
    return(rom_num);
}

int * adder(int * a, int * b, int * c)
{
    //Custom large number adding, which makes each digit of a large
    //number into a separate integer in an array. Each pair is added
    //by index, and manually carrying any remaining 'ones'.
    int carry = 0;
    int sum = 0;
    int start = 128 - 1;
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
    //Fibonacci using custom large number adding.
    a[127] = 1;
    b[127] = 1;
    fibno = fibno - 2;

    while(fibno > 0)
    {
        c = adder(a, b, c);

        //print_num_array(c);

        memcpy(a, b, 128 * sizeof(int));
        memcpy(b, c, 128 * sizeof(int));

        --fibno;
    }
}

void make_array(char * string, int * num, int start)
{
    //Makes an array from recieved string.
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


