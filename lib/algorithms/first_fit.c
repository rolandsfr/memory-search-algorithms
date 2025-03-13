#include <algorithms.h>
#include <parsers.h>

#define MEM_SIZE 1024

unsigned char mybuffer[MEM_SIZE];

void *myalloc(size_t size) {
  size_t free_space;
  size_t alloc_start;
  size_t i;

  if (size == 0 || size > MEM_SIZE) {
    return NULL;
  }

  for (size_t start_index = 0; start_index < MEM_SIZE; start_index++) {
    free_space = 0;

    while (free_space < size && start_index + free_space < MEM_SIZE) {
      if (mybuffer[start_index + free_space] == 0) {
        free_space++;
      } else {
        break;
      }
    }

    if (free_space >= size) {
      alloc_start = start_index;
      for (i = 0; i < size; i++) {
        mybuffer[alloc_start + i] = 1;
      }
      return &mybuffer[alloc_start];
    }
  }

  return NULL;
}

void search_first_fit(FILE* stream) {
  int num;

  while ( (num = read_next_int(stream)) != EOF) {
    void *ptr = myalloc(sizeof(int));
    if (ptr != NULL) {
      printf("[ INFO ] Allocated %lu bytes at address %p\n", sizeof(int), ptr);
    } else {
      printf("[ ERROR ] Failed to allocate %lu bytes\n", sizeof(int));
    }
  }
}

SearchAlgorithm search_first_fit_runner = {
  .start = search_first_fit
};
