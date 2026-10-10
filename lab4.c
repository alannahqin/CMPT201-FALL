
#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define HEAP_SIZE 256
#define BLOCK_SIZE 128
#define BUF_SIZE 100

struct header {
  uint64_t size;
  struct header *next;
};

// print numbers using write
void print_number(char *format, uint64_t number) {
  char buf[BUF_SIZE];
  int len = snprintf(buf, sizeof(buf), format, number);

  if (len > 0 && len < BUF_SIZE) {
    write(STDOUT_FILENO, buf, len);
  }
}

// print addresses using write
void print_address(char *format, void *address) {
  char buf[BUF_SIZE];
  int len = snprintf(buf, sizeof(buf), format, address);

  if (len > 0 && len < BUF_SIZE) {
    write(STDOUT_FILENO, buf, len);
  }
}

// MAIN FUNCTION
int main(void) {
  void *memory = sbrk(HEAP_SIZE);

  if (memory == (void *)-1) {
    write(STDERR_FILENO, "sbrk failed\n", 12);
    return 1;
  }
  struct header *first = (struct header *)memory;
  struct header *second = (struct header *)((char *)memory + BLOCK_SIZE);

  // set up the block headers
  first->size = BLOCK_SIZE;
  first->next = NULL;

  second->size = BLOCK_SIZE;
  second->next = first;

  // set the data of the first block to 0 and second to 1
  char *data1 = (char *)(first + 1);
  size_t data_size = BLOCK_SIZE - sizeof(struct header);
  memset(data1, 0, data_size);
  char *data2 = (char *)(second + 1);
  memset(data2, 1, data_size);

  // print addresses and header information
  print_address("first block:       %p\n", first);
  print_address("second block:      %p\n", second);

  print_number("first block size:  %lu\n", first->size);
  print_address("first block next:  %p\n", first->next);

  print_number("second block size: %lu\n", second->size);
  print_address("second block next: %p\n", second->next);

  // print every byte of the first and second block's data
  for (size_t i = 0; i < data_size; i++) {
    print_number("%lu\n", (unsigned char)data1[i]);
  }

  for (size_t i = 0; i < data_size; i++) {
    print_number("%lu\n", (unsigned char)data2[i]);
  }

  return 0;
}
