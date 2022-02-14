#include <stdio.h> // for printf()
long long factorial (long long value)
{
    if (value == 1) {
        return (1);
    } else {
        return (value * factorial (value - 1));
    }
} // factorial
int main (int argc, char *argv[])
{
    printf ("factorial of 16 is %lld\n", factorial(6));
    return (0);
} // main