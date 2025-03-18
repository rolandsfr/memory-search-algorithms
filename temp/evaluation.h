#include <stdio.h>

#ifndef EVALUATION_H
#define EVALUATION_H

typedef struct Node {
    long int value;
    int is_free;
    struct Node* next;
} Node;

typedef struct EvaluationResult {
    double time_taken;
    double fragmentation_ratio;
} EvaluationResult;

double calculate_fragmentation(Node* memory, int largest_request);
EvaluationResult evaluate_algorithm(void (*algorithm)(FILE*, FILE*), FILE* chunks_fs, FILE* sizes_fs, Node* memory, int largest_request);
Node* create_list(FILE* stream);

#endif /* EVALUATION_H */
