#include <stdlib.h>
#include <algorithms.h>
#include <parsers.h>
#include <evaluation.h>

#define MEMORY_CAP 1024

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
    Node* memory_head = create_list(chunks_fs);
    Node* memory = memory_head;

    int size;
    int total_allocated_size = 0;
    int allocations_succeeded = 0;
    int largest_req = get_largest_req(sizes_fs);
    clock_t start, end;
   
    start = clock();

    while((size = read_next_int(sizes_fs)) != EOF) {
        Node* min = find_min(size, memory);

        // stop the loop if nothing can ever fit in
        if(total_allocated_size == MEMORY_CAP) break;

        // skip if we the memeory cannot afford to store requested size
        if(min != NULL && total_allocated_size + min->value > MEMORY_CAP) {
            continue;
        }

        if(min != NULL) {
            min->is_free = 0;
            total_allocated_size += min->value;
            allocations_succeeded++;
            // uncomment for detailed debug
            // printf("Chunk for %d -> %d\n", size, min->value);
        } 

        memory = memory_head;
    } 
    
    end = clock();

    printf(" - Time taken, seconds: %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    printf(" - Fragmentation ratio: %f\n", calculate_fragmentation(memory, largest_req));
    printf(" - Allocated blocks: %d\n", allocations_succeeded);
    printf(" - Total memory allocated, bytes: %d\n", total_allocated_size);

    end = clock();

    printf("Allocations succeeded: %d\nTotal memory allocated: %d\n", allocations_succeeded, total_allocated_size);

}


SearchAlgorithm search_best_fit_runner = {
    .start = search_best_fit
};

