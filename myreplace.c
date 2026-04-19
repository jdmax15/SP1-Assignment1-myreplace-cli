


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
#define MAX_PAIRS	50

struct Pair {
    char *from;
    char *to;
    int replace;
};




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
		printf("argc: %d\n", argc);
	}


	struct Pair pairs[MAX_PAIRS];
	int pairCount = 0;
	int pairStart;

	int fArgUsed = 0;
	char fArg[] = "-f";
	if ((strcmp(argv[2], fArg)) == 0) {
		printf("-f arg used.\n");
		fArgUsed = 1;
	} else {
		printf("-f arg NOT used.\n");
	}

	char *file;
	
	if (fArgUsed) {
		file = argv[1];
		pairStart = 3;
	} else {
		file = argv[2];
		pairStart = 2;
	}

	for (int i = pairStart; i < argc; i += 2) {
		pairs[pairCount].from = argv[i];
		pairs[pairCount].to	= argv[i+1];
		pairs[pairCount].replace = 0;
		pairCount++;
	}
	
	printf("Printing Pairs: \n");

	for (int i = 0; i < pairCount; i++) {
		printf("Pair[%d].from = %s\n", i, pairs[i].from);
		printf("Pair[%d].to = %s\n", i, pairs[i].to);
		printf("Pair[%d].replace = %d\n", i, pairs[i].replace);
	}

	// int fd;
	// ssize_t nread;
	// char buffer[BUFFERSIZE];

	// fd = open(file, O_RDWR);
	// if (fd == -1) {
	// 	printf("Error: Could not open %s\n", file);
	// }
	// printf("file descriptor is %d\n\n", fd);



	// while ((nread = read(fd, buffer, BUFFERSIZE)) > 0) {
	// 	for (int i = 0; i < nread; i++) {
	// 		if (buffer[i] == *from) {
	// 			buffer[i] = *to;
	// 		}
	// 	}
	// 	lseek(fd, -nread, SEEK_CUR);
	// 	write(fd, buffer, nread);
	// 	write(1, buffer, nread);
	// }


	// close(fd);

	

	return 0;
}
