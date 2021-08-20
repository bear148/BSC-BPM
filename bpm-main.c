#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char version[] = "1.0.0";

int main(int argc, char *argv[]) {
	char* option = argv[1];
	char* packageToInstall = argv[2];
	char* packageToInstall1 = argv[2];
	char op1[] = "install";
	char op2[] = "remove";
	char op3[] = "--version";
	char bla[70];
	char bla2[70];
	if (strcmp(option, op1) == 0) {
		/*char packageRepo[] = "https://github.com/Bear-Package-Management/%s", packageToInstall;
		char destinaton[] = "/usr/local/bpm-packages/%s", packageToInstall1;*/
		snprintf(bla, sizeof(bla), "Bear-Package-Management/%s", packageToInstall);
		snprintf(bla2, sizeof(bla), "/usr/local/bpm-packages/%s", packageToInstall);
		char* args[] = {"/usr/bin/gh", "repo", "clone", bla, bla2, NULL};

		pid_t pid;
		if ((pid = fork()) < 0) {     /* fork a child process           */
			printf("*** ERROR: forking child process failed\n");
			exit(1);
		}
		else if (pid == 0) {          /* for the child process:         */
			if (execvp("git", args) < 0) {     /* execute the command  */
				printf("*** ERROR: exec failed\n");
				exit(1);
			}
		}
		else {                                  /* for the parent:      */
			wait(&pid);
			return 0;
		}
	} else if (strcmp(option, op2) == 0) {
		printf("Not finished.\n");
	} else if (strcmp(option, op3) == 0) {
		printf("BPM Package Manager v%s\n", version);
		printf("Coded By: Michael S.\n");
		printf("(c) Michael S. 2021\n");
	}
	exit(EXIT_SUCCESS);
}