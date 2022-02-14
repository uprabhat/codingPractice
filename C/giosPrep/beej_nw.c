#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <netinet/in.h>

//#define RUN_TRIALS
#define RUN_getaddrinfo

#ifdef RUN_TRIALS
int main(void) {
    struct sockaddr_in sa; // IPv4
    struct sockaddr_in6 sa6; // IPv6
    inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4
    char ip4[INET_ADDRSTRLEN]; // space to hold the IPv4 string
    inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

    printf("Output>>> %d == %s\n",sa.sin_addr.s_addr,ip4);
}
#endif

#ifdef RUN_getaddrinfo
int main(int argc, char *argv[])
{
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];
	if (argc != 2) {
		fprintf(stderr,"usage: showip hostname\n");
		return 1;
    }
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}
	printf("IP addresses for %s:\n\n", argv[1]);
	for(p = res;p != NULL; p = p->ai_next) {
		void *addr;
		char *ipver;
		// get the pointer to the address itself,
		// different fields in IPv4 and IPv6:
		if (p->ai_family == AF_INET) { // IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else { // IPv6
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}
		// convert the IP to a string and print it:
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		
        int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        bind(sockfd, res->ai_addr, res->ai_addrlen);
		printf(" %s: %s SOCKET=%d\n", ipver, ipstr,sockfd);
	}
	freeaddrinfo(res); // free the linked list
	return 0;
}
#endif