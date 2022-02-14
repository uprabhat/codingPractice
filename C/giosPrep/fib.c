#include <stdio.h>

int fib_iter(int num) {
    if (num==1 || num==2) {
        return(1);
    } else {
        int n1=1;
        int n2=1;
        int sum;
        for(int i=num;i>2;i--) {
            sum=n2+n1;
            n1=n2;
            n2=sum;
        }
        return(n2);
    }
}

int fib_recur(int num) {
    if(num<=2){
        return 1;
    } else {
        return(fib_recur(num-1)+fib_recur(num-2));
    }
}

int main() {
    int num;
    printf("Enter an integer:");
    scanf("%d",&num);
    if(fib_iter(num)==fib_recur(num)) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
    printf("Iter=%d,Recur=%d\n",fib_iter(num),fib_recur(num));
    return(0);
}