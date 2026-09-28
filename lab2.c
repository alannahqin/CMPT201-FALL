#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  // variables
  char *line = NULL;
  size_t size = 0;
  while (1) {
    printf("Enter programs to run.\n> ");

    // get program path from user
    if (getline(&line, &size, stdin) == -1) {
      free(line);
      return 1;
    }

    // remove newline from input
    for (int i = 0; line[i] != '\0'; i++) {
      if (line[i] == '\n') {
        line[i] = '\0';
        break;
      }
    }

    // create child
    pid_t pid = fork();
    if (pid < 0) {
      printf("Fork failure\n");
      free(line);
      return 1;
    }

    // child process
    if (pid == 0) {
      execlp(line, line, NULL);
      printf("Exec failure\n");
      free(line);
      exit(1);
    } else {
      // parent waits for child
      if (waitpid(pid, NULL, 0) == -1) {
        printf("Wait failure\n");
        free(line);
        return 1;
      }
    }
  }

  // free memory
  free(line);
  return 0;
}
