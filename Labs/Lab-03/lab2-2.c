#include <stdio.h>

int main(void)
{
    // Start the block with the declaration and initialisation of the local variables
    int i = -1;
    char my_string[16];

    printf("Please enter an integer\n");
    scanf("%i", &i);
    printf("You typed \"%i\"\n", i);

    printf("Please enter a string (in other words anything)\n");
    scanf("%15s", &my_string);
    printf("You typed \"%s\"\n", my_string);

    return 0;
}
