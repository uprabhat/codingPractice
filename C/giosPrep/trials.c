#include <stdio.h>
#include <string.h>
#if 0 //play with char pointer & strings
int main() {
    char *s;
    char str[]="This is a string";
    s=str; //UTK: char pointer to head string
    printf("%s",s);
    printf("\n");

    char *p="Hello"; //UTK: char pointer to head string
    printf("%s\n",p);
    p++;
    printf("%s\n",p); //keep printing chars till \0 is encountered
    printf("%c\n",p); //Tries to convert the 'int' address into char and print
    printf("%c\n",*p); //Prints only the first element in array
    printf("%d\n",p); //Prints only the first element in array
    printf("%c\n",p[2]); //Prints only the 2th element in array
    printf("%c\n",*(p+2)); //Prints only the 2th element in array


    return(0);
}
#endif
  typedef struct {
	int pos; //3:SOF 2:MOF 1:EOF 0:Not a file
	int flag; //0:Write(not read yet) 1:Read
	char *data;
  } shm_ds;

void proxy_shMem2DS (char* inStr, shm_ds* outDs) {
  int off=0;
  outDs->pos      =*(inStr+off);
  off+=sizeof(int);
  outDs->flag     =*(inStr+off);
  off+=sizeof(int);
  outDs->data     =(inStr+off);
}

void proxy_DS2shMem (shm_ds* inDs,char* outStr) {
  int offset=(2*sizeof(int));
  memcpy(outStr,inDs,offset);
  memcpy(outStr+offset,inDs->data,strlen(inDs->data));
}

#if 0 //play with program args
int main(int argc, char* argv[]) {
    printf("Printing argv----->\n");
    for (int i=0;i<argc;i++) {
        printf("%d : %s\n",i,argv[i]);
    }gg
    printf("\n");
    return(0);
}
#endif
#include <stdlib.h>
#if 1
int main() {
    for(int i=0;i<3;i++) {
        printf("Inside loop i=%d\n",i);
    }

    char *shMem=(char *)malloc(200);
    shm_ds lclMem,lclMem2;
    lclMem.pos=1;
    lclMem.flag=2;
    lclMem.data="This is the string";
    printf("LCLMEM=[%d %d %s]\n",lclMem.pos,lclMem.flag,lclMem.data);
    proxy_DS2shMem(&lclMem,shMem);
    printf("SHMEM=%s\n",shMem+2*(sizeof(int)));
    proxy_shMem2DS(shMem,&lclMem2);
    printf("LCLMEM2=[%d %d %s]",lclMem2.pos,lclMem2.flag,lclMem2.data);
    return(1);
    //printf("Outside loop i=%d",i); // Gives an error
    int f;
    int z=(f=sizeof(int));
    printf("z=%d\n",z);
    char myStr[100] ; //="A B\rC\nD\tE"; //9
    char newStr[100];
    //int x=sprintf(myStr,"A B\rC\nD\tE");
    int x=sprintf(myStr,"GETFILE OK 18446744073709551616\r\n\r\n");
    int y=sprintf(newStr,"%s\n\n%s",myStr,myStr);

    printf("Writing %lu/%lu bytes x=%d y=%d\n",strlen(newStr),sizeof(newStr),x,y);
    FILE *fh=fopen("my.bin","wb");
    fwrite(newStr,strlen(newStr),1,fh);
    fclose(fh);
    printf("%lu\n",sizeof(int));
    char mStr[]=" ";
    if (mStr[0]==' ') { printf("space\n"); } 

    char delim[] = " ";

	char *ptr = strtok(myStr, delim);

	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, " ");
	}
      
}
#endif

#if 0
//Source: https://www.programmingsimplified.com/c/source-code/c-substring
void substring(char *out, char *in, int strt, int end) {
   int p = strt; //position
   while (p < end) {
      out[p] = in[p-1];
      p++;
   }
   out[p] = '\0';
}


int proxy_shMem2DS (char* inStr, shm_ds* outDs) {
  int ret=1;
  int off=0;
  int inc=sizeof(long int)-1;
  outDs->srcThread=inStr[off];
  outDs->pos      =inStr;
  outDs->flag     =inStr;
  outDs->bytes    =inStr;
  outDs->data     =inStr;
}


#endif
