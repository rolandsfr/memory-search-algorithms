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

#endif /* EVALUATION_H */
