
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // check each block until one is large enough
  while (free_list_ptr != NULL) {
    if (free_list_ptr->size >= size) {
      return free_list_ptr->id;
    }
    free_list_ptr = free_list_ptr->next;
  }

  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t best_size = UINT64_MAX;

  // find the smallest block that can fit request
  while (free_list_ptr != NULL) {
    if (free_list_ptr->size >= size && free_list_ptr->size < best_size) {
      best_size = free_list_ptr->size;
      best_fit_id = free_list_ptr->id;
    }
    free_list_ptr = free_list_ptr->next;
  }

  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  uint64_t worst_size = 0;

  // find the largest block that can fit request
  while (free_list_ptr != NULL) {
    if (free_list_ptr->size >= size && free_list_ptr->size > worst_size) {
      worst_size = free_list_ptr->size;
      worst_fit_id = free_list_ptr->id;
    }
    free_list_ptr = free_list_ptr->next;
  }

  return worst_fit_id;
}

int main(void) {
  // create five free blocks
  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  // set the sizes, next pointers, and IDs
  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  // find a free block for a request of size 7
  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // print the IDs of the blocks found
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  // free the memory used for the blocks
  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}
