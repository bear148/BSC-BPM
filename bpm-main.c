#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdbool.h>

char version[] = "3.2.1";

void updateLog() {
	printf("BPM-BSC Official Update Log\n");
	printf("Current Version: %s\n", version);
	printf("-----------------------------\n");
	printf("Update 3.2.1:\n");
	printf("\tInstallation of third-party repositories now is used like this: 'bpm install --link <link>'\n");
	printf("\tMan page added. 'man bpm'\n");
	printf("\tAll arguments other than 'install' and 'remove' have two dashes before! For example, 'bpm update-log' is now 'bpm --update-log'\n");
	printf("\t--update Option\n");
	printf("\t[Bug Fix] When a command executes, it now either returns 1 or 0.\n");
	return;
}

void helpCom() {
	printf("BPM-BSC v%s Official Help Page\n", version);
	printf("-----------------------------\n");
	printf("BPM Usage: bpm <option> <package>\n");
	printf("\tOptions:\n");
	printf("\t\tremove:       removes given package\n");
	printf("\t\tinstall:      installs given package\n");
	printf("\t\t--update-log: shows what was added in the most recent version\n");
	printf("\t\t--version:    shows current bpm version\n");
	printf("\t\t--help: 	  shows list of working commands\n");
	printf("\t\t--package: 	  shows list of working commands\n");
	printf("\t\t--update:     updates bpm\n");
	printf("\t\tArguments:\n");
	printf("\t\t\tpackage has 1 argument, '--list'\n");
	printf("\tCommands with 4 or more Args:\n");
	printf("\t\tUsage: bpm <option> <arg> <arg1>\n");
	printf("\t\t\tOptions: (Options that have 4 argument compatability)\n");
	printf("\t\t\t\tinstall: Installs package\n");
	printf("\t\tArg:\n");
	printf("\t\t\t--link: Allows user to install from links\n");
	printf("\t\tArg1:\n");
	printf("\t\t\tCurrently, for arg1 you can only use links since as of 8/24/21, the install option\n");
	printf("\t\t\tis the only option that can use 4 args, like so: 'bpm install --link https://foo'\n");
	return;
}

void fullInstallPackage(char* package) {
	return;
}

int check_url(char *url)
{
	CURL *curl;
	CURLcode response;
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
		response = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return (response == CURLE_OK) ? 1 : 0;
}

bool StartsWith(const char *a, const char *b) {
   if(strncmp(a, b, strlen(b)) == 0) {
	   return 1;
   }
   return 0;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("[E]: No argument given.\n");
		helpCom();
	} else {
		char* option = argv[1];
		char* packageToInstall = argv[2];
		char* packageToInstall1 = argv[2];
		char op1[] = "install";
		char op2[] = "remove";
		char op3[] = "--version";
		char op4[] = "--package";
		char op5[] = "--update-log";
		char op6[] = "--help";
		char op7[] = "--update";
		char arg1[] = "--link";
		char dontDownload[] = "BPM-Repositories";
		char bla[70];
		char bla2[70];
		if (strcmp(option, op1) == 0) {
			if (strcmp(argv[2], arg1) == 0) {
				char* linkToInstall = argv[3];
				if (StartsWith(linkToInstall, "https://")) {
					int result = check_url(packageToInstall);
					if (result) {
						char* token = getenv("API");
						printf("Warning! You're downloading an unofficial BPM Repository! We are not responsible for damages!\n");
						snprintf(bla, sizeof(bla), linkToInstall);
						snprintf(bla2, sizeof(bla), "/usr/local/bpm-packages/%s", linkToInstall);
						char* args[] = {"git", "clone", bla, bla2, NULL};
						if (strcmp(linkToInstall, dontDownload) == 0) {
							printf("[E]: You can't download this repository!\n");
							printf("[E]: The repo '%s' is an admin repo!\n", linkToInstall);
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
								return 1;
							}
						}
					} else {
						printf("[E]: The link you gave is not valid!\n");
						return 0;
					}
				} else {
					printf("[E]: That isn't a link!\n");
					return 0;
				}
			} else {
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
						return 1;
					}
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
				return 1;
			}
		} else if (strcmp(option, op3) == 0) {
			printf("BPM Package Manager v%s\n", version);
			printf("Coded By: Michael S.\n");
			printf("(c) Michael S. 2021\n");
		} else if (strcmp(option, op4) == 0) {
			char* arg1 = argv[2];
			if (strcmp(arg1, "--list") == 0) {
				char* args[] = {"ls", "-al", "/usr/local/bpm-packages", NULL};
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
					return 1;
				}
			} else {
				printf("[E]: Not a sub-option for the option 'package'\n");
				return 0;
			}
		} else if (strcmp(option, op5) == 0) {
			updateLog();
			return 1;
		} else if (strcmp(option, op6) == 0) {
			helpCom();
			return 1;
		} else if (strcmp(option, op7) == 0) {
			printf("[W]: To update, please do 'make update' in the directory of BSC-BPM\n");
			return 1;
		} else {
			printf("[E]: Not a bpm command!\n");
		}
	}
	exit(EXIT_SUCCESS);
}