#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFERSIZE	1024
#define MAX_PAIRS	50

struct Pair {
    char *from;
    char *to;
    int replace;
};


int main (int argc, char *argv[]) {

	if (argc < 3) {
		printf("Usage: \"myreplace [-f] filename from to [from to] ...\" \n");
		return -1;
	}

	struct Pair pairs[MAX_PAIRS];
	int pairCount = 0;
	int pairStart;

	int fArgUsed = 0;
	char fArg[] = "-f";
	if ((strcmp(argv[1], fArg)) == 0) {
		fArgUsed = 1;
	}
	
	char *file;
	
	if (fArgUsed) {
		file = argv[2];
		pairStart = 3;
	} else {
		file = argv[1];
		pairStart = 2;
	}

	if ((fArgUsed && (argc % 2 != 1)) || (!fArgUsed && (argc % 2 != 0))) {
		printf("ERROR: Enter \"from\" and \"to\" as pairs. Odd number detected.\n");
		exit(1);
	}


	for (int i = pairStart; i < argc; i += 2) {
		pairs[pairCount].from = argv[i];
		pairs[pairCount].to	= argv[i+1];
		pairs[pairCount].replace = 0;
		pairCount++;
	}

	int fd;
	ssize_t nread;
	char buffer[BUFFERSIZE];

	fd = open(file, O_RDWR);
	if (fd == -1) {
		printf("\nERROR: Could not open %s\n", file);
		exit(1);
	}

	while ((nread = read(fd, buffer, BUFFERSIZE)) > 0) {
		for (int i = 0; i < nread; i++) {
			for (int j = 0; j < pairCount; j++) {
				if (strncmp(buffer + i, pairs[j].from, strlen(pairs[j].from)) == 0) {
					if (fArgUsed && pairs[j].replace == 1) {
						break;
					} else {			
						if (strcmp(pairs[j].from, pairs[j].to) != 0) {
								memcpy(buffer + i, pairs[j].to, strlen(pairs[j].to));
								pairs[j].replace = 1;
						}
						i += strlen(pairs[j].from) - 1;
						break;
					}
				}
			}
		}

		if (lseek(fd, -nread, SEEK_CUR) == -1) {
			printf("\nERROR: lseek failure.\n");
			exit(1);
		}

		if (write(fd, buffer, (size_t)nread) == -1) {
			printf("\nERROR: write failure.\n");
			exit(1);
		}

		write(1, buffer, (size_t)nread);
	}

	if (nread == -1) {
		printf("\nERROR: could not read from file.\n");
		exit(1);
	}

	int wasModified = 0;
	for (int i = 0; i < pairCount; i++) {
		if (pairs[i].replace == 1) {
			wasModified = 1;
			break;
		}
	}
	if (wasModified) {
		printf("\nFile was modified.\n");
	} else {
		printf("\nFile was not modified.\n");
	}

	
	close(fd);


	return 0;
}
