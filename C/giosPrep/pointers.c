#include <stdio.h> // for printf()
#if 0
void addemUp (int a, int b, int *result)
{
    *result = a + b;
} // addemUp

int main (int argc, char *argv[])
{
    int answer;
    addemUp (1, 2, &answer);
    printf ("1 + 2 = %d\n", answer);
    return (0);
} // main
#endif

#if 0
int main (int argc, char *argv[])
{
    char *myString = "this is a sequence of chars";
    int length = 0;
    while (*myString != '\0') {
        length++;
        myString++;
    }
    printf ("the length of the string is %d\n", length);
    return (0);
} // main
#endif

#if 0
int main (int argc, char *argv[])
{
    char *myString = "this is a sequence of chars";
    int length = 0;
    while (*myString++) { //increment ptr addr and then use * to fetch value
        length++;
    }
    printf ("the length of the string is %d\n", length);
    return (0);
} // main
#endif

#if 1
#include <stdio.h> // for printf()
void printAsChar (int value)
{
    printf ("%d as a char is '%c'\n", value, value);
} // printAsChar

void printAsInt (int value)
{
    printf ("%d as an int is '%d'\n", value, value);
} // printAsInt

void printAsHex (int value)
{
    printf ("%d as hex is '0x%x'\n", value, value);
} // printAsHex

void printIt (int value, void (*printingFunction)(int))
{
    (printingFunction)(value);
} // printIt

int main (int argc, char *argv[])
{
    int value = 35;
    printIt (value, printAsChar);
    printIt (value, printAsInt);
    printIt (value, printAsHex);
    return (0);
} // main
#endif