#include <stdio.h>

int main(void)
{
    // Start the block with the declaration and initialisation of the local variables
    int i = -1;
    unsigned int ui = -1;

    short s = -2;
    unsigned short us = -2;

    char c = 255;
    unsigned char uc = 255;

    float f = -1.2;
    double d = -1.4;

    char* string = "Hey you!";

    printf("To print an int in C, I need: %i\n", i);
    printf("To print an unsigned int in C, I need: %u\n", ui);

    printf("To print a short in C, I need: %i\n", s);
    printf("To print an unsigned short in C, I need: %u\n", us);

    printf("To print a char in C, I need: %i\n", c);
    printf("To print an unsigned char in C, I need: %u\n", uc);

    printf("To print a float in C, I need: %f\n", f);
    printf("To print a double in C, I need: %f\n", d);

    printf("To print a string in C, I need: %s\n", string);

    return 0;
}
