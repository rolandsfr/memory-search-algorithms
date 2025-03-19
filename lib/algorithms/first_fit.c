#include <stdlib.h>
#include <algorithms.h>
#include <parsers.h>
#include <evaluation.h>
#include <time.h>

#define MEMORY_CAP 1024

// typedef struct Node {
//   long int value;
//   int is_free;
//   struct Node* next;
// } Node;


Node* create_ff_node(int value) {
  Node* node = (Node*)(malloc(sizeof(Node)));
  node->value = value;
  node->next = NULL;
  node->is_free = 1;
  return node;
}

Node* create_ff_list(FILE* stream) {
  int num;
  Node* head = NULL;
  Node* tail = NULL;

  while((num = read_next_int(stream)) != EOF) {
    Node* node = create_ff_node(num);
    if(head == NULL) {
      head = node;
      tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
  }

  return head;
}

Node* find_first_fit(int size, Node* memory) {
  Node* curr = memory;

  while (curr != NULL) {
    if (curr->is_free && curr->value >= size) {
      return curr;
    }
    curr = curr->next;
  }

  return NULL; 
}

void search_first_fit_0(FILE* chunks_fs , FILE* sizes_fs) {
  Node* memory = create_ff_list(chunks_fs);

  int size;
  int total_allocated_size = 0;
  int allocations_succeeded = 0;
  while((size = read_next_int(sizes_fs)) != EOF) {
    if(total_allocated_size + size > MEMORY_CAP) break;

    Node* first_fit = find_first_fit(size, memory);

    if(first_fit != NULL) {
      first_fit->is_free = 0;
      total_allocated_size += size;
      allocations_succeeded++;
      /* uncomment for detailed debug 
      printf("Chunk for %d -> %lu\n", size, (unsigned long)(first_fit->value));*/
    } 
  } 

  printf("Allocations succeeded: %d\nTotal memory allocated: %d\n", allocations_succeeded, total_allocated_size);
}

void search_first_fit(FILE* chunks_fs, FILE* sizes_fs) {
  Node* memory = create_ff_list(chunks_fs);
  Node* first_fit = NULL;
  int size;
  clock_t start, end;
  int total_allocated_size = 0;
  int allocations_succeeded = 0;
  int largest_req = get_largest_req(sizes_fs);

  start = clock();

  while((size = read_next_int(sizes_fs)) != EOF) {
    if(total_allocated_size + size > MEMORY_CAP) {
      break;
    }

    first_fit = find_first_fit(size, memory);

    if(first_fit != NULL) {
      first_fit->is_free = 0;
      total_allocated_size += size;
      allocations_succeeded++;
    }
  }

  /* Beidzam mērīt laiku */
  end = clock();

  print_results(start, end, memory, largest_req, allocations_succeeded, total_allocated_size);

}

SearchAlgorithm search_first_fit_runner = {
  .start = search_first_fit
};

