#include <algorithms.h>
#include <parsers.h>
#include <time.h>
#include <evaluation.h>

/* Pieņemt, ka izdalītās atmiņas kopējais apjoms ir 1024 baiti. */
#define MEMORY_CAP 1024

Node* create_nf_node(int value) {
  Node* node = (Node*)(malloc(sizeof(Node)));
  node->value = value;
  node->next = NULL;
  node->is_free = 1;
  return node;
}

Node* create_nf_list(FILE* stream) {
  int num;
  Node* head = NULL;
  Node* tail = NULL;

  while((num = read_next_int(stream)) != EOF) {
    Node* node = create_nf_node(num);
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

Node* find_next_fit(int size, Node* memory, Node** last_alloc) {
  Node* curr = *last_alloc ? (*last_alloc)->next : memory;

  while (curr != NULL) {
    if (curr->is_free && curr->value >= size) {
      *last_alloc = curr;
      return curr;
    }
    curr = curr->next;
  }

  curr = memory;
  while (curr != *last_alloc) {
    if (curr->is_free && curr->value >= size) {
      *last_alloc = curr;
      return curr;
    }
    curr = curr->next;
  }

  return NULL; 
}

void search_next_fit(FILE* chunks_fs, FILE* sizes_fs) {
  Node* memory = create_nf_list(chunks_fs);
  Node* last_alloc = NULL;
  clock_t start, end;
  int size;
  int total_allocated_size = 0;
  int allocations_succeeded = 0;
  int largest_request = get_largest_req(sizes_fs);

  /* Sākam mērīt laiku */
  start = clock();

  while((size = read_next_int(sizes_fs)) != EOF) {
    if(total_allocated_size + size > MEMORY_CAP) break;

    Node* next_fit = find_next_fit(size, memory, &last_alloc);

    if(next_fit != NULL) {
      next_fit->is_free = 0;
      total_allocated_size += size;
      allocations_succeeded++;
    } 
  } 
  /* Beidzam mērīt laiku */
  end = clock();

  print_results(start, end, memory, largest_request, allocations_succeeded, total_allocated_size);
}

SearchAlgorithm search_next_fit_runner = {
  .start = search_next_fit
};
