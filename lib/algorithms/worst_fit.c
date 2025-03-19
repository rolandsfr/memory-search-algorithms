#include <stdlib.h>
#include <algorithms.h>
#include <parsers.h>
#include <evaluation.h>


#define MEMORY_CAP 1024

// typedef struct Node {
//     long int value;
//     int is_free;
//     struct Node* next;
// } Node;

static Node* create_node(int value) {
    Node* node = (Node*)(malloc(sizeof(Node)));
    node->value = value;
    node->next = NULL;
    node->is_free = 1;
    return node;
}

static Node* create_list(FILE* stream) {
    int num;
    Node* head = NULL;
    Node* tail = NULL;

    while((num = read_next_int(stream)) != EOF) {
        Node* node = create_node(num);
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

static Node* find_max(int start, Node* memory) {
    Node* head = memory;
    Node* curr = memory;
    Node* max = NULL;

    while (curr != NULL) {
        if (curr->is_free && curr->value >= start && curr->value <= MEMORY_CAP) {
            if (max == NULL || curr->value > max->value) {
                max = curr;
            }

        }
        curr = curr->next;
    }

    return max; 
}


void search_worst_fit(FILE* chunks_fs , FILE* sizes_fs) {
    // store head seperately, to reset current memory block pointer when needed
    Node* memory_head = create_list(chunks_fs);
    Node* memory = memory_head;

    clock_t start, end;
    int largest_request = 0;

    int size;
    int total_allocated_size = 0;
    int allocations_succeeded = 0;

    while((size = read_next_int(sizes_fs)) != EOF) {
      if (size > largest_request) {
        largest_request = size;
      }
    }
    rewind(sizes_fs);
    start = clock();

    while((size = read_next_int(sizes_fs)) != EOF) {
        Node* max = find_max(size, memory);
            
        if(total_allocated_size == MEMORY_CAP) break;

        if(max != NULL && total_allocated_size + max->value > MEMORY_CAP) {
            break;
        }


        if(max != NULL) {
            max->is_free = 0;
            total_allocated_size += max->value;
            allocations_succeeded++;
            // uncomment for detailed debug
            // printf("Chunk for %d -> %d\n", size, max->value);
        } 

        memory = memory_head;
    } 

    end = clock();

    printf("Allocations succeeded: %d\nTotal memory allocated: %d\n", allocations_succeeded, total_allocated_size);

    printf(" - Time taken, seconds: %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    printf(" - Fragmentation ratio: %f\n", calculate_fragmentation(memory, largest_request));
    printf(" - Allocated blocks: %d\n", allocations_succeeded);
    printf(" - Total memory allocated, bytes: %d\n", total_allocated_size);


}


SearchAlgorithm search_worst_fit_runner = {
    .start = search_worst_fit
};

