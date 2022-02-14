#include <stdio.h>
#include <string.h>

#if 0
int main(void)
{
FILE *fp; // Variable to represent open file

fp = fopen("hello.txt", "r"); // Open file for reading -> check for NULL if any error
char c;

while ( (c= fgetc(fp)) != EOF) { // Read a single character till EOF reached
    printf("%c", c); // Print char to stdout
}

fclose(fp); // Close the file when done
}
#endif

#if 0
int main(void)
{
    FILE *fp;
    char s[1024]; // Big enough for any line this program will encounter
    int linecount = 0;

    fp = fopen("hello.txt", "r");
    while (fgets(s, sizeof s, fp) != NULL)
        printf("%d: %s", ++linecount, s);
    fclose(fp);
}
#endif

#if 0
int main(void)
{
    FILE *fp;
    char name[1024]; // Big enough for any line this program will encounter
    float length;
    int mass;
    fp = fopen("whales.txt", "r");
    while (fscanf(fp, "%s %f %d", name, &length, &mass) != EOF)
        printf("%s whale, %d tonnes, %.1f meters\n", name, mass, length);
    fclose(fp);
}
#endif

#if 0
int main(void)
{
    FILE *fp;
    int x = 32;
    fp = fopen("output.txt", "w");
    fputc('B', fp);
    fputc('\n', fp);
    fprintf(fp, "x = %d\n", x);
    fputs("Hello, world!\n", fp);
    fclose(fp);
}
#endif

#if 0
int main(void)
{
    FILE *fp;
    unsigned char bytes[] = {5, 37, 0, 88, 255, 12};
    fp = fopen("output.bin", "wb"); // wb mode for "write binary"!
    // In the call to fwrite, the arguments are:
    //
    // * Pointer to data to write
    // * Size of each "piece" of data
    // * Count of each "piece" of data
    // * FILE*
    fwrite(bytes, sizeof(char), sizeof bytes, fp);
    fclose(fp);
}
#endif

#if 0
int main(void)
{
    FILE *fp;
    unsigned char c;
    fp = fopen("output.bin", "rb"); // rb for "read binary"!
    while (fread(&c, sizeof(char), 1, fp) > 0)
        printf("%d\n", c);
}
#endif

#if 1 //adjusting buffer size to line
#include <stdlib.h>

// Returns a pointer to the line
// Returns NULL on EOF or error.
// It's up to the caller to free() this pointer when done with it.

char* readline(FILE *fp) {
    int bufSize=sizeof(char); //start with 2 bytes - at least two characters - we will work in powers of 2
    char inC;
    char *line;
    line=(char*)malloc(bufSize);
    line[0]='\0';
    int charCnt=1;

    while( (  inC=fgetc(fp)  )!=EOF) { //till we hit eof
        if( inC !='\n') {
            charCnt++;
            if( charCnt > bufSize ) {
                bufSize*=2;
                line=(char*)realloc(line,bufSize);
            } else if (charCnt<=(bufSize-1)) {
                bufSize=charCnt*sizeof(char);
                line=(char*)realloc(line,bufSize);
            }
        } else {
            return(line); //return pointer to line
        }
        line[charCnt-2]=inC;
        line[charCnt-1]='\0';
    }
    return(NULL); //return null if nothing is read or error
}

int main() {
    FILE *fp=fopen("hello.txt","r");
    char *line;
    int i=1;
    while((line=readline(fp))!=NULL) {
        printf("%d\t%s\n",i,line);
        free(line);
        i++;
    }
    fclose(fp);
    return(0);
}

#endif

#if 0 //another code from book
#include <stdio.h>
#include <stdlib.h>

// Read a line of arbitrary size from a file
//
// Returns a pointer to the line.
// Returns NULL on EOF or error.
//
// It's up to the caller to free() this pointer when done with it.
 //
 // Note that this strips the newline from the result. If you need
 // it in there, probably best to switch this to a do-while.

 char *readline(FILE *fp)
 {
 int offset = 0; // Index next char goes in the buffer
 int bufsize = 4; // Preferably power of 2 initial size
 char *buf; // The buffer
 int c; // The character we've read in

 buf = malloc(bufsize); // Allocate initial buffer

 if (buf == NULL) // Error check
 return NULL;

 // Main loop--read until newline or EOF
 while (c = fgetc(fp), c != '\n' && c != EOF) {

 // Check if we're out of room in the buffer accounting
 // for the extra byte for the NUL terminator
 if (offset == bufsize - 1) { // -1 for the NUL terminator
 bufsize *= 2; // 2x the space

 char *new_buf = realloc(buf, bufsize);

 if (new_buf == NULL) {
 free(buf); // On error, free and bail
 return NULL;

 }

 buf = new_buf; // Successful realloc
 }

 buf[offset++] = c; // Add the byte onto the buffer
 }

 // We hit newline or EOF...

 // If at EOF and we read no bytes, free the buffer and
 // return NULL to indicate we're at EOF:
 if (c == EOF && offset == 0) {
 free(buf);
 return NULL;
 }

 // Shrink to fit
 if (offset < bufsize - 1) { // If we're short of the end
 char *new_buf = realloc(buf, offset + 1); // +1 for NUL terminator

 // If successful, point buf to new_buf;
 // otherwise we'll just leave buf where it is
 if (new_buf != NULL)
 buf = new_buf;
 }

 // Add the NUL terminator
 buf[offset] = '\0';

 return buf;
 }

 int main(void)
 {
 FILE *fp = fopen("hello.txt", "r");

 char *line;

 while ((line = readline(fp)) != NULL) {
 printf("%s\n", line);
 free(line);
 }

 fclose(fp);
 }
#endif