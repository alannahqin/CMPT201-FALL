#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *line = NULL;
  size_t size = 0;

  // loop to prompt
  while (1) {
    printf("Please enter some text: ");
    ssize_t read = getline(&line, &size, stdin);

    if (read == -1) {
      break;
    }

    printf("Tokens:\n");
    char *saveptr = NULL;
    char *token = strtok_r(line, " \n", &saveptr);

    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, " \n", &saveptr);
    }
  }

  free(line);

  return 0;
}
