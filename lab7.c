
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 100

typedef struct {
  int line_number;
  int value;
} Input;

typedef struct {
  int line_number;
  int doubled_value;
} IntermediateInput;

typedef struct {
  int doubled_value;
  int line_numbers[MAX_INPUT];
  int count;
} Output;

void map(Input *input, IntermediateInput *intermediate_input) {
  // double the number
  intermediate_input->line_number = input->line_number;
  intermediate_input->doubled_value = input->value * 2;
}

void groupByKey(IntermediateInput *input, Output *output, int *result_count) {
  int i;

  // check if the value is already there
  for (i = 0; i < *result_count; i++) {
    if (output[i].doubled_value == input->doubled_value) {
      output[i].line_numbers[output[i].count] = input->line_number;
      output[i].count++;
      return;
    }
  }

  // if not found then add a new one
  output[*result_count].doubled_value = input->doubled_value;
  output[*result_count].line_numbers[0] = input->line_number;
  output[*result_count].count = 1;
  (*result_count)++;
}

void reduce(Output *output) {
  printf("(%d, [", output->doubled_value);

  for (int i = 0; i < output->count; i++) {
    printf("%d", output->line_numbers[i]);

    if (i != output->count - 1) {
      printf(", ");
    }
  }

  printf("])\n");
}

int main() {
  Input inputs[MAX_INPUT];
  IntermediateInput intermediate[MAX_INPUT];
  Output outputs[MAX_INPUT] = {0};

  int input_count = 0;
  int result_count = 0;
  char str[100];

  printf("Enter values (one per line). Type 'end' to finish:\n");

  while (input_count < MAX_INPUT) {
    if (fgets(str, sizeof(str), stdin) == NULL) {
      break;
    }

    if (strncmp(str, "end", 3) == 0) {
      break;
    }

    int num;
    if (sscanf(str, "%d", &num) == 1) {
      inputs[input_count].line_number = input_count + 1;
      inputs[input_count].value = num;
      input_count++;
    }
  }

  // map all inputs
  for (int i = 0; i < input_count; i++) {
    map(&inputs[i], &intermediate[i]);
  }

  // group same numbers
  for (int i = 0; i < input_count; i++) {
    groupByKey(&intermediate[i], outputs, &result_count);
  }

  // print everything
  for (int i = 0; i < result_count; i++) {
    reduce(&outputs[i]);
  }

  return 0;
}
