#include <stdio.h>
#define PI 3.14159
#define Version "beta5"
// make some macros
#define SQUARE(x) ((x) * (x))
#define AreaOfACircle(r) (PI * SQUARE(r))

int main (int argc, char *argv[])
{
    printf ("Welcome to version %s of macros\n", Version);
    printf ("The area of a circle with radius 5 is %f\n", AreaOfACircle(5));

    #define THING1
    #ifdef THING1
        printf ("thing1 defined\n");
    #else
        printf ("thing1 is not defined\n");
    #endif
    #ifdef THING2
        printf ("thing2 is defined\n");
    #else
        printf ("thing2 is not defined\n");
    #endif

    #if 0
        printf ("oh happy day\n");
        printf ("bork bork bork\n");
        we_can even have syntax errors in here
        since the compiler will never see this part
    #endif
    #if 1
        printf ("this is included. wheee.\n");
    #endif

    return (0);
} // main