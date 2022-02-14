#include <stdio.h> // for printf()

#if 0
int main (int argc, char *argv[])
{
    printf ("some integer constants: %d %d %d %d\n",1, 3, 32767, -521);
    printf ("some floating-point constants: %f %f %f %f\n",3.14159, 1.414213, 1.5, 2.0);
    printf ("single character constants: %c%c%c%c%c\n",'W', 'P', '\114', '\125', '\107');
    printf ("and finally a character string constant: '%s'\n","this is a string");
    return (0);
} // main
#endif

#if 0
#include <limits.h> // for limit constants
#include <stdio.h> // for printf()
#include <stdlib.h> // for EXIT_SUCCESS
int main (int argc, char *argv[])
{
    printf (" type: bytes %14s %14s %14s\n", "min value", "max value", "max unsigned");
    printf (" char: %5ld %14d %14d %14u\n", sizeof(char), CHAR_MIN, CHAR_MAX, UCHAR_MAX);
    printf (" short: %5ld %14d %14d %14u\n", sizeof(short), SHRT_MIN, SHRT_MAX, USHRT_MAX);
    printf (" int: %5ld %14d %14d %14u\n", sizeof(int), INT_MIN, INT_MAX, UINT_MAX);
    printf (" long: %5ld %14ld %14ld %14lu\n", sizeof(long), LONG_MIN, LONG_MAX, ULONG_MAX);
    // not available on all platforms
    #ifdef LLONG_MIN
        printf (" long long: %5ld %20lld %20lld \n"
        " %20llu\n", sizeof(long long),LLONG_MIN, LLONG_MAX, (long long)ULLONG_MAX);
    #endif
    printf (" float: %5ld\n", sizeof(float));
    printf (" double: %5ld\n", sizeof(double));
    return (EXIT_SUCCESS);
} // main
#endif

#if 0
int aGlobalInt; // global
float pi = 3.14159; // global
void someFunction ()
{
    int aLocalVariable = 0; // local, random value but
    // initialized to zero
    unsigned short myShort; // local, random value
    static unsigned char aByte; // static, initialized to
    // zero, persists
    myShort = 500 + aLocalVariable;
    aGlobalInt = 5;
    aByte++;
    printf ("aByte: %d, myShort: %d aGlobalInt: %d\n", aByte, myShort, aGlobalInt);
} // someFunction
int main (int argc, char *argv[])
{
    printf ("aGlobalInt before someFunction: %d\n", aGlobalInt);
    someFunction ();
    printf( "aGlobalInt after someFunction: %d\n", aGlobalInt);
    someFunction ();
    aGlobalInt = 23;
    someFunction ();
    return (0);
} // main
#endif