#include <stdio.h>
#include <time.h>

#ifndef EVALUATION_H
#define EVALUATION_H

typedef struct Node {
    long int value;
    int is_free;
    struct Node* next;
} Node;

double calculate_fragmentation(Node* memory, int largest_request);

int get_largest_req(FILE* sizes_fs);

void print_results(clock_t start, clock_t end, Node* memory, int largest_request, int allocations_succeeded, int total_allocated_size);

#endif /* EVALUATION_H */
