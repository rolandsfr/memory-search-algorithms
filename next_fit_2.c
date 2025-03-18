#include <algorithms.h>
#include <parsers.h>
#include <time.h>

#define MEM_SIZE 1024

unsigned char mybuffer_nextfit[MEM_SIZE];
size_t next_fit_index = 0;

// Function to calculate fragmentation
double calculate_fragmentation_nextfit(int largest_request) {
  size_t total_free = 0;
  size_t largest_free_block = 0;
  size_t current_free_block = 0;
  
  // Count free bytes and find largest free block
  for (size_t i = 0; i < MEM_SIZE; i++) {
    if (mybuffer_nextfit[i] == 0) {
      total_free++;
      current_free_block++;
      if (current_free_block > largest_free_block) {
        largest_free_block = current_free_block;
      }
    } else {
      current_free_block = 0;
    }
  }
  
  // If no free memory, fragmentation is 0
  if (total_free == 0) return 0.0;
  
  // Calculate unusable memory (free bytes that can't satisfy largest request)
  size_t unusable_memory = 0;
  current_free_block = 0;
  
  for (size_t i = 0; i < MEM_SIZE; i++) {
    if (mybuffer_nextfit[i] == 0) {
      current_free_block++;
    } else {
      if (current_free_block > 0 && current_free_block < (size_t)largest_request) {
        unusable_memory += current_free_block;
      }
      current_free_block = 0;
    }
  }
  
  // Check the last block
  if (current_free_block > 0 && current_free_block < (size_t)largest_request) {
    unusable_memory += current_free_block;
  }
  
  // Calculate fragmentation ratio
  return (double)unusable_memory / total_free;
}

void *nextfit_alloc(size_t size) {
  size_t start_index;
  size_t free_space;
  size_t alloc_start;
  size_t i;

  if (size == 0 || size > MEM_SIZE) {
    return NULL;
  }
  
  start_index = next_fit_index;
  free_space = 0;

  while (free_space < size) {
    if (mybuffer_nextfit[next_fit_index] == 0) {
      free_space++;
    } else {
      free_space = 0;
    }

    next_fit_index = (next_fit_index + 1) % MEM_SIZE;

    if (next_fit_index == start_index) {
      return NULL;
    }
  }

  alloc_start = (next_fit_index + MEM_SIZE - free_space) % MEM_SIZE;
  for (i = 0; i < size; i++) {
    mybuffer_nextfit[alloc_start + i] = 1;
  }

  next_fit_index = (alloc_start + size) % MEM_SIZE;
  return &mybuffer_nextfit[alloc_start];
}

/* Free allocated memory */
void nextfit_free(void *ptr, size_t size) {
  if (ptr == NULL || ptr < (void *)mybuffer_nextfit || 
      ptr >= (void *)(mybuffer_nextfit + MEM_SIZE)) {
    return; // Invalid pointer
  }
  
  size_t alloc_start = (unsigned char *)ptr - mybuffer_nextfit;
  for (size_t i = 0; i < size && (alloc_start + i) < MEM_SIZE; i++) {
    mybuffer_nextfit[alloc_start + i] = 0;
  }
}

void search_next_fit(FILE* chunks_fs, FILE* sizes_fs) {
  int i;
  int chunk, size;
  void *ptr = NULL;
  int largest_request = 0;
  clock_t start_total, end_total;
  double total_time = 0.0;

  // Initialize memory buffer to all zeros (free)
  for (i = 0; i < MEM_SIZE; i++) {
    mybuffer_nextfit[i] = 0;
  }
  
  // Reset next fit index to start from beginning
  next_fit_index = 0;
  
  // Start timing the entire algorithm
  start_total = clock();

  while ((chunk = read_next_int(chunks_fs)) != EOF && (size = read_next_int(sizes_fs)) != EOF) {
    // Track largest request for fragmentation calculation
    if (size > largest_request) {
      largest_request = size;
    }
    // Skip invalid values
    if (chunk <= 0 || size <= 0) {
      printf("[ ERROR ] Invalid chunk or size value: chunk=%d, size=%d\n", chunk, size);
      continue;
    }

    // Check if size is too large for our memory
    if (size > MEM_SIZE) {
      printf("[ ERROR ] Requested size %d exceeds memory size %d\n", size, MEM_SIZE);
      continue;
    }

    int success_count = 0;
    clock_t start_alloc, end_alloc;
    
    // Time this specific allocation set
    start_alloc = clock();
    
    // Try to allocate 'chunk' number of blocks of 'size' bytes each
    for (i = 0; i < chunk; i++) {
      ptr = nextfit_alloc(size);
      if (ptr != NULL) {
        success_count++;
      }
    }
    
    end_alloc = clock();
    double alloc_time = ((double) (end_alloc - start_alloc)) / CLOCKS_PER_SEC;
    
    // Calculate fragmentation after this allocation set
    double frag_ratio = calculate_fragmentation_nextfit(largest_request);
    
    printf("[ INFO ] Next Fit: Allocated %d/%d blocks of %d bytes each\n", 
           success_count, chunk, size);
    printf("[ FRAG ] Fragmentation ratio: %.4f\n", frag_ratio);
    printf("[ PERF ] Allocation time: %.6f seconds\n", alloc_time);
  }
  
  // End timing the entire algorithm
  end_total = clock();
  total_time = ((double) (end_total - start_total)) / CLOCKS_PER_SEC;
  
  // Calculate final fragmentation
  double final_frag = calculate_fragmentation_nextfit(largest_request);
  
  // Report final statistics
  printf("\n[ SUMMARY ] Next Fit Algorithm\n");
  printf("[ SUMMARY ] Total execution time: %.6f seconds\n", total_time);
  printf("[ SUMMARY ] Final fragmentation ratio: %.4f\n", final_frag);
}

SearchAlgorithm search_next_fit_runner = {
  .start = search_next_fit
};