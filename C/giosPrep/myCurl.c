#include <stdio.h>
#include <unistd.h>
#include "curl/curl.h"
size_t got_data(char *buffer, size_t itemsize, size_t nItems, void * nothing) {
	size_t bytes= itemsize*nItems;
	int line=1;
	printf("New chunk (%zu bytes)\r",bytes);
    sleep(1);
	//printf("%d:\t",line);
	for (int i=0; i<bytes; i++) {
        //printf("%c",buffer[i]);
		if(buffer[i]=='\n') {
			line++;
            //printf("%d:\t",line);
		}
	}
	return bytes;
}


int main() {
      setbuf(stdout, NULL);
      FILE * fh=fopen("tmp.bin","wb");
	//INIT CURL
	CURL *curl=curl_easy_init();
	if(!curl) {
		printf("Error 1");
	}
	//set options CURL
	//curl_easy_setopt(curl,CURLOPT_URL,"https://raw.githubusercontent.com/gt-cs6200/image_data/master/1kb-sample-file-0.png");
	curl_easy_setopt(curl,CURLOPT_URL,"https://raw.githubusercontent.com/gt-cs6200/image_data/master/1kb-sample-file-1.html");
	//curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,got_data); //callback function: got_data
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,fh);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);

	//Perform CURL
	CURLcode result=curl_easy_perform(curl);
	if(result!=CURLE_OK) {
		printf("Error %s\n",curl_easy_strerror(result));
	}
    double cl;
    CURLcode res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &cl);
    if(!res) {
      printf("\nSize: %.0f\n", cl);
    }

	//cleanup curl
    fclose(fh);
	curl_easy_cleanup(curl);
}
