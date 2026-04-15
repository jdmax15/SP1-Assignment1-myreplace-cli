


#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define COPYMODE	0644
#define BUFFERSIZE	1024

int main (int argc, char *argv[]) {

	if (argc < 2) {
		printf("Usage: \"myreplace [-f] filename from to [from to] ...\" \n");
		return -1;
	}

	if (argc > 0) {
		for (int i = 0; i < argc; i++) {
			printf("argv[%d]: %s \n", i, argv[i]);
		}
		printf("\n");
	}

	char *to;
	char *from;

	int fArgUsed = 0;
	char fArg[] = "-f";
	if ((strcmp(argv[1], fArg)) == 0) {
		printf("-f arg used.\n");
		fArgUsed = 1;
	} else {
		printf("-f arg NOT used.\n");
	}

	char *file;
	
	if (fArgUsed) {
		file = argv[2];
		from = argv[3];
		to = argv[4];
	} else {
		file = argv[1];
		from = argv[2];
		to = argv[3];
	}

	printf("from = %c\n", *from);
	printf("to = %c\n", *to);

	int fd;
	ssize_t nread;
	char buffer[BUFFERSIZE];

	fd=open(file, O_RDWR);
	if (fd == -1) {
		printf("Error: Could not open %s\n", file);
	}
	printf("file descriptor is %d\n\n", fd);



	while ((nread = read(fd, buffer, BUFFERSIZE)) > 0) {
		for (int i = 0; i < nread; i++) {
			if (buffer[i] == *from) {
				buffer[i] = *to;
			}
		}
		lseek(fd, -nread, SEEK_CUR);
		write(fd, buffer, nread);
		write(1, buffer, nread);
	}


	close(fd);

	

	return 0;
}
