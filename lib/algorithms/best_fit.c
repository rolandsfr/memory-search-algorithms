#include <stdlib.h>
#include <algorithms.h>
#include <parsers.h>

#define MEMORY_CAP 1024

typedef struct Node {
    long int value;
    int is_free;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* node = (Node*)(malloc(sizeof(Node)));
    node->value = value;
    node->next = NULL;
    node->is_free = 1;
    return node;
}

Node* create_list(FILE* stream) {
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

Node* find_min(int start, Node* memory) {
    Node* curr = memory;
    Node* min = NULL;

    while (curr != NULL) {
        if (curr->is_free && curr->value >= start) {
            if (min == NULL || curr->value < min->value) {
                min = curr;
                
                if(min->value == start) return min;
            }
        }
        curr = curr->next;
    }

    return min; 
}


void search_best_fit(FILE* chunks_fs , FILE* sizes_fs) {
    Node* memory = create_list(chunks_fs);

    int size;
    int total_allocated_size = 0;
    int allocations_succeeded = 0;
    while((size = read_next_int(sizes_fs)) != EOF) {
        if(total_allocated_size + size > MEMORY_CAP) break;

        Node* min = find_min(size, memory);

        if(min != NULL) {
            min->is_free = 0;
            total_allocated_size += size;
            allocations_succeeded++;
            // uncomment for detailed debug
            // printf("Chunk for %d -> %d\n", size, min->value);
        } 
    } 

    printf("Allocations succeeded: %d\nTotal memory allocated: %d\n", allocations_succeeded, total_allocated_size);

}


SearchAlgorithm search_best_fit_runner = {
    .start = search_best_fit
};

