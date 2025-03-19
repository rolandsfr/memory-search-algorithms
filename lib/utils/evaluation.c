#include <stdio.h>
#include <time.h>
#include <parsers.h>
#include "evaluation.h"

int get_largest_req(FILE* sizes_fs) {
  int size;
  int largest_request = 0;

  while((size = read_next_int(sizes_fs)) != EOF) {
    if (size > largest_request) {
      largest_request = size;
    }
  }
  rewind(sizes_fs); 

  return largest_request;
}

void print_results(clock_t start, clock_t end, Node* memory, int largest_request, int allocations_succeeded, int total_allocated_size) {
  printf(" - Time taken, seconds: %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
  printf(" - Fragmentation ratio: %f\n", calculate_fragmentation(memory, largest_request));
  printf(" - Allocated blocks: %d\n", allocations_succeeded);
  printf(" - Total memory allocated, bytes: %d\n", total_allocated_size);
}

double calculate_fragmentation(Node* memory, int largest_request) {
  size_t total_free = 0;
  size_t largest_free_block = 0;
  size_t current_free_block = 0;
  
  Node* curr = memory;
  while (curr != NULL) {
    if (curr->is_free) {
      total_free += curr->value;
      current_free_block += curr->value;
      if (current_free_block > largest_free_block) {
        largest_free_block = current_free_block;
      }
    } else {
      current_free_block = 0;
    }
    curr = curr->next;
  }
    
  if (total_free == 0) return 0.0;
  
  size_t unusable_memory = 0;
  current_free_block = 0;
  curr = memory;
  while (curr != NULL) {
    if (curr->is_free) {
      current_free_block += curr->value;
    } else {
      if (current_free_block > 0 && current_free_block < (size_t)largest_request) {
        unusable_memory += current_free_block;
      }
      current_free_block = 0;
    }
    curr = curr->next;
  }
    
  if (current_free_block > 0 && current_free_block < (size_t)largest_request) {
    unusable_memory += current_free_block;
  }
  
  return (double)unusable_memory / total_free;
}

// double calculate_fragmentation2(Node* memory, int largest_request) {
//   size_t total_free = 0;
//   size_t largest_free_block = 0;
//   size_t current_free_block = 0;
//   size_t unusable_memory = 0;
  
//   Node* curr = memory;
//   while (curr != NULL) {
//     if (curr->is_free) {
//       total_free += curr->value;
//       current_free_block += curr->value;
//       if (current_free_block > largest_free_block) {
//         largest_free_block = current_free_block;
//       }
//     } else {
//       current_free_block = 0;
//     }
//     curr = curr->next;
//   }
    
//   if (total_free == 0) return 0.0;
  
//   current_free_block = 0;
//   curr = memory;
//   while (curr != NULL) {
//     if (curr->is_free) {
//       current_free_block += curr->value;
//     } else {
//       if (current_free_block > 0 && current_free_block < (size_t)largest_request) {
//         unusable_memory += current_free_block;
//       }
//       current_free_block = 0;
//     }
//     curr = curr->next;
//   }
    
//   if (current_free_block > 0 && current_free_block < (size_t)largest_request) {
//     unusable_memory += current_free_block;
//   }
  
//   return (double)unusable_memory / total_free;
// }