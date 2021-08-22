#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char version[] = "2.1.0";

void updateLog() {
	printf("BPM-BSC Official Update Log\n");
	printf("Current Version: %s\n", version);
	printf("-----------------------------\n");
	printf("Update 2.1.0:\n");
	printf("\tInstallation no longer requires login\n");
	printf("\tPackages now installed from BPM-Repositories and not Bear-Package-Management\n");
	return;
}

void helpCom() {
	printf("BPM-BSC v%s Official Help Page\n", version);
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

void fullInstallPackage(char* package) {

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
	char dontDownload[] = "BPM-Repositories";
	char bla[70];
	char bla2[70];
	if (strcmp(option, op1) == 0) {
		char* token = getenv("API");
		snprintf(bla, sizeof(bla), "https://%s@github.com/BPM-Repositories/%s.git", token, packageToInstall);
		snprintf(bla2, sizeof(bla), "/usr/local/bpm-packages/%s", packageToInstall);
		char* args[] = {"git", "clone", bla, bla2, NULL};
		if (strcmp(packageToInstall, dontDownload) == 0) {
			printf("[E]: You can't download this repository!\n");
			printf("[E]: The repo '%s' is an admin repo!\n", packageToInstall);
			return 0;
		} else {
			pid_t pid;
			if ((pid = fork()) < 0) {     /* fork a child process           */
				printf("[E]: forking child process failed\n");
				exit(1);
			}
			else if (pid == 0) {          /* for the child process:         */
				if (execvp("git", args) < 0) {     /* execute the command  */
					printf("[E]: exec failed\n");
					exit(1);
				}
			}
			else {                                  /* for the parent:      */
				wait(&pid);
				return 0;
			}
		}
	} else if (strcmp(option, op2) == 0) {
		char* packageToRemove = argv[2];
		char blaFoobar[70];
		snprintf(blaFoobar, sizeof(bla), "/usr/local/bpm-packages/%s", packageToRemove);
		char* args[] = {"rm", "-r", blaFoobar, NULL};
		pid_t pid;
		if ((pid = fork()) < 0) {
			printf("[E]: forking child process failed\n");
			exit(1);
		}
		else if (pid == 0) {
			if (execvp("rm", args) < 0) {
				printf("[E]: exec failed\n");
				exit(1);
			}
		}
		else {
			wait(&pid);
			printf("[O]: Successfully removed %s\n", packageToRemove);
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
				printf("[E]: forking child process failed\n");
				exit(1);
			}
			else if (pid == 0) {
				if (execvp("ls", args) < 0) {
					printf("[E]: exec failed\n");
					exit(1);
				}
			}
			else {
				wait(&pid);
				return 0;
			}
		} else {
			printf("[E]: Not a sub-option for the option 'package'\n");
		}
	} else if (strcmp(option, op5) == 0) {
		updateLog();
		return 0;
	} else if (strcmp(option, op6) == 0) {
		helpCom();
		return 0;
	} else {
		printf("[E]: Not a bpm command!\n");
	}
	exit(EXIT_SUCCESS);
}