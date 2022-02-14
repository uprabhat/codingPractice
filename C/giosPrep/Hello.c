#include <stdio.h>
#include "tools.h"

int main() {
   // printf() displays the string inside quotation
   int a=1;
   printf("Hello, World!\n");
   char  c2=dumpencrypt('A');
   int sum=add(2,3);
   printf("Hello again - %c - %d",c2,sum);
   return 0;
}