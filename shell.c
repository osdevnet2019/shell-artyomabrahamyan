#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

void show_prompt(uid_t current_usr_id) {
  if (current_usr_id == 0) {
    printf("shell# ");
  } 
  else {
    printf("shell$ ");
  }
}

void read(char * argv[], int * is_background) {
  const int inputsize = 256;
  char str[inputsize];
  fgets(str, inputsize, stdin);

  char * pch = strtok(str, " \n");
  int i = 0;

  while (pch != NULL) {
	if (strcmp("&", pch) == 0) {
        * is_background = 1;
      } 
	else {
        argv[i++] = pch;
	}  
    pch = strtok(NULL, " \n");    
  }

  argv[i++] = 0;
}

int main() {
  uid_t id = getuid();
  int is_background = 0;

  while(1){
  show_prompt(id);

  char * argv[10];
  read(argv, & is_background);

  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  if (pid > 0 && is_background == 0) {
    wait();
  } 
  else if (pid > 0 && is_background == 1) {}
  else {
    execvp(argv[0], argv);
    fprintf(stderr, "Unable to execute bash command", 30);
  }
  }

  return 0;
}