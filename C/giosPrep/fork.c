#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
//#include <stdlib.h>

#if 0
int main () {
    pid_t pid;
    int status;
    /*fork a child*/
    pid=fork();

    if (pid<0) { /*error*/
        fprintf(stderr,"Fork Failed");
        exit(-1);
    } else if (pid == 0) { /*child process*/
        printf("child process, pid = %u\n",getpid());
        printf("parent of child process, pid = %u\n",getppid()); 
        execlp("/bin/ls","ls",NULL);
        /*  If execlp() is successful, we should not reach this next line. */
        printf("The call to execlp() was not successful.\n");
    } else {
        /*parent waits for child*/
        printf("Parent Of parent process, pid = %u\n",getppid());
        printf("parent process, pid = %u\n",getpid()); 
        //wait(NULL);
        if (waitpid(pid, &status, 0) > 0) {
              
            if (WIFEXITED(status) && !WEXITSTATUS(status)) 
              printf("child program execution successful\n");
              
            else if (WIFEXITED(status) && WEXITSTATUS(status)) {
                if (WEXITSTATUS(status) == 127) {
  
                    // execlp failed
                    printf("execlp failed\n");
                }
                else 
                    printf("program terminated normally,"
                       " but returned a non-zero status\n");                
            }
            else 
               printf("program didn't terminate normally\n");            
        } 
        else {
           // waitpid() failed
           printf("waitpid() failed\n");
        }
        exit(0);
    }
}
#endif

#if 1

int main () {
    printf("Hello"); //without \n, it stays in buffer, since buffer is copied in fork, Hello will be printed twice
    fork();
}
#endif