#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char version[] = "2.0.0";

void updateLog() {
	printf("BPM-BSC Official Update Log\n");
	printf("Current Version: %s\n", version);
	printf("-----------------------------\n");
	printf("Update 2.0.0:\n");
	printf("\tAdded package option with --list arg.\n");
	printf("\tinstall option now works and installs commands.\n");
	printf("\tremove option now works and removes packages.\n");
	printf("\tupdate-log option now works and shows what is added in the most recent update.\n");
	printf("\tAdded help command. 'bpm --help'\n");
	return;
}

void helpCom() {
	printf("BPM-BSC Official Help Page\n");
	printf("Current Version: %s\n", version);
	printf("-----------------------------\n");
	printf("BPM Usage: bpm <option> <package>\n");
	printf("\tOptions:\n");
	printf("\t\tremove:     removes given package\n");
	printf("\t\tinstall:    installs given package\n");
	printf("\t\tupdate-log: shows what was added in the most recent version\n");
	printf("\t\t--version:  shows current bpm version\n");
	printf("\t\t--help: 	shows list of working commands\n");
	printf("\t\tpackage: 	shows list of working commands\n");
	printf("\t\tArguments:\n");
	printf("\t\t\tpackage has 1 argument, '--list'\n");
	return;
}

int main(int argc, char *argv[]) {
	char* option = argv[1];
	char* packageToInstall = argv[2];
	char* packageToInstall1 = argv[2];
	char op1[] = "install";
	char op2[] = "remove";
	char op3[] = "--version";
	char op4[] = "package";
	char op5[] = "update-log";
	char op6[] = "--help";
	char bla[70];
	char bla2[70];
	if (strcmp(option, op1) == 0) {
		/*char packageRepo[] = "https://github.com/Bear-Package-Management/%s", packageToInstall;
		char destinaton[] = "/usr/local/bpm-packages/%s", packageToInstall1;*/
		snprintf(bla, sizeof(bla), "https://github.com/Bear-Package-Management/%s", packageToInstall);
		snprintf(bla2, sizeof(bla), "/usr/local/bpm-packages/%s", packageToInstall);
		char* args[] = {"git", "clone", bla, bla2, NULL};

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
		char* packageToRemove = argv[2];
		char blaFoobar[70];
		snprintf(blaFoobar, sizeof(bla), "/usr/local/bpm-packages/%s", packageToRemove);
		char* args[] = {"rm", "-r", blaFoobar, NULL};
		pid_t pid;
		if ((pid = fork()) < 0) {
			printf("*** ERROR: forking child process failed\n");
			exit(1);
		}
		else if (pid == 0) {
			if (execvp("rm", args) < 0) {
				printf("*** ERROR: exec failed\n");
				exit(1);
			}
		}
		else {
			wait(&pid);
			printf("Successfully removed %s\n", packageToRemove);
			return 0;
		}
	} else if (strcmp(option, op3) == 0) {
		printf("BPM Package Manager v%s\n", version);
		printf("Coded By: Michael S.\n");
		printf("(c) Michael S. 2021\n");
	} else if (strcmp(option, op4) == 0) {
		char* arg1 = argv[2];
		if (strcmp(arg1, "--list") == 0) {
			char* args[] = {"ls", "/usr/local/bpm-packages", NULL};
			pid_t pid;
			if ((pid = fork()) < 0) {
				printf("*** ERROR: forking child process failed\n");
				exit(1);
			}
			else if (pid == 0) {
				if (execvp("ls", args) < 0) {
					printf("*** ERROR: exec failed\n");
					exit(1);
				}
			}
			else {
				wait(&pid);
				return 0;
			}
		} else {
			printf("Not a sub-option for the option 'package'\n");
		}
	} else if (strcmp(option, op5) == 0) {
		updateLog();
		return 0;
	} else if (strcmp(option, op6) == 0) {
		helpCom();
		return 0;
	} else {
		printf("Not a bpm command!\n");
	}
	exit(EXIT_SUCCESS);
}