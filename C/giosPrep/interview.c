#include <stdio.h>
#include <math.h>
#define AVERAGE(x,y) (((x) + (y) )/ 2)

int main (int argc, char *argv[])
{
    int a=3;
    printf("Cosine of 1 is %g\n",cos(1.0));
    printf("<1>%d\n",AVERAGE(2,3));
    printf("Thank you\n");
    printf("<2>%d\n",!(1&1));
    int arr[5]={1,2,3,4};
    printf("%d\n",arr[4]);
    printf("%zu\n",sizeof(arr));
    char *ptr="This is a longer stirng";
    printf("PTR:%zu\n",sizeof(*ptr));
    char strArr[50]="This is a longer string";
    printf("ARR:%zu\n",sizeof(strArr));
    int b=2;
    int *intPtr;
    intPtr=&b;
    //*intPtr=b;
    printf("INT-PTR:%zu=%p=%d\n",sizeof(intPtr),intPtr,*intPtr);
    char myC=5["abxdef"];
    printf("<3>,%c\n",myC);
    return(0);
}