#include<stdio.h>

int main(void)
{
	int a[5] = { 5, 4, 3, 2, 1 };
	int b[10] = { 2, 1 }; // elements b[2] to b[9] will be set to 0
	int c[10] = {}; // all elements will be set to 0
	int d[10];  // The elements in d will be uninitialized

	for (unsigned int i = 0; i < 5; ++i)
	{
		printf("a[%i] = %i\n", i, a[i]);
	}
	printf("\n");

	for (unsigned int i = 0; i < 10; ++i)
	{
		printf("b[%i] = %i\n", i, b[i]);
	}
	printf("\n");
	
	for (unsigned int i = 0; i < 10; ++i)
	{
		printf("c[%i] = %i\n", i, c[i]);
	}
	printf("\n");
	
	for (unsigned int i = 0; i < 10; ++i)
	{
		printf("d[%i] = %i\n", i, d[i]);
	}

	return 0;
}
