#include <stdio.h>
#include <time.h>
#include "evaluation.h"

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