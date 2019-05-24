#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 2048
#define SERVICE_PORT 2222

int main()
{
    printf("Initializing...\n");

	struct sockaddr_in localaddr;	// our address
	struct sockaddr_in remoteaddr;	// remote address
	socklen_t addrlen = sizeof(remoteaddr); // length of addresses
	ssize_t recvlen;			// bytes received
	int fd;				// socket
    int sockoptval = 1; // option value
	unsigned char buf[BUFSIZE];	// buffer

	// create UDP socket
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}

	// use setsockopt to set SO_REUSEADDR
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &sockoptval, sizeof(int)) < 0) {
		perror("setsockopt failed\n");
		return 0;
	}

	// bind socket to all IP addresses and port SERVICE_PORT
	memset((char *)&localaddr, 0, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&localaddr, sizeof(localaddr)) < 0) {
		perror("bind failed");
		return 0;
	}

	// now loop, receiving data and printing what we received
	for (;;) {
		printf("waiting on port %d\n", SERVICE_PORT);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remoteaddr, &addrlen);
		printf("received %d bytes\n", recvlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			printf("received message: \"%s\"\n", buf);
		}
	}

	// never exits
}