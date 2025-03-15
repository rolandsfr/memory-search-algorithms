#include <algorithms.h>
#include <parsers.h>

#define MEM_SIZE 1024

unsigned char mybuffer_firstfit[MEM_SIZE];

void *firstfit_alloc(size_t size) {
  size_t free_space;
  size_t alloc_start;
  size_t i;

  if (size == 0 || size > MEM_SIZE) {
    return NULL;
  }

  for (size_t start_index = 0; start_index < MEM_SIZE; start_index++) {
    free_space = 0;

    while (free_space < size && start_index + free_space < MEM_SIZE) {
      if (mybuffer_firstfit[start_index + free_space] == 0) {
        free_space++;
      } else {
        break;
      }
    }

    if (free_space >= size) {
      alloc_start = start_index;
      for (i = 0; i < size; i++) {
        mybuffer_firstfit[alloc_start + i] = 1;
      }
      return &mybuffer_firstfit[alloc_start];
    }
  }

  return NULL;
}

void search_first_fit(FILE* chunks_fs, FILE* sizes_fs) {
  int num;

  while ( (num = read_next_int(chunks_fs)) != EOF) {
    void *ptr = firstfit_alloc(sizeof(int));
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
