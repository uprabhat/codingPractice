#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t start_t, curr_t;
    start_t=time(NULL);
    printf("Timeout program\n");
    sleep(3);
    curr_t=time(NULL);
    printf("Time diff = %d secs\n",(int)difftime(curr_t,start_t));

}
