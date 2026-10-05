#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

void add_history(char *history[], int *count, const char *input) {
  char *copy = strdup(input);

  if (copy == NULL) {
    return;
  }

  if (*count < HISTORY_SIZE) {
    history[*count] = copy;
    (*count)++;
  } else {
    // remove the oldest input
    free(history[0]);

    // move everything left
    for (int i = 0; i < HISTORY_SIZE - 1; i++) {
      history[i] = history[i + 1];
    }

    history[HISTORY_SIZE - 1] = copy;
  }
}

void print_history(char *history[], int count) {
  for (int i = 0; i < count; i++) {
    printf("%s\n", history[i]);
  }
}

void free_history(char *history[], int count) {
  for (int i = 0; i < count; i++) {
    free(history[i]);
  }
}

//--------------------------
// MAIN FUNCTION
//--------------------------
int main(void) {
  char *history[HISTORY_SIZE] = {NULL};
  int history_count = 0;

  char *line = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter input: ");

    if (getline(&line, &size, stdin) == -1) {
      break;
    }

    // remove the newline from getline
    size_t length = strlen(line);

    if (length > 0 && line[length - 1] == '\n') {
      line[length - 1] = '\0';
    }

    // save every input, including blank lines and "print"
    add_history(history, &history_count, line);

    // if the user typed print, show the current history
    if (strcmp(line, "print") == 0) {
      print_history(history, history_count);
    }
  }

  free_history(history, history_count);
  free(line);

  return 0;
}
