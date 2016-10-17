#include <cstdio>
#include <cstring>
int main()
{
    char hi[] = "Hi";
    strcat(hi, "ya");
    const char* name = "John";
    if (strcmp(name, "John") == 0)
        printf("%s %s!\n", hi, name);

	return 0;
}
