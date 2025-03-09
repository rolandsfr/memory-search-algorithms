#include <stdio.h>

/* 
    SearchAlgorithm struct for virtual function definition
*/
typedef struct SearchAlgorithm {
    // search algorithms returns nothing as soon as appropriate chunk is found
    // accepts a files stream that can use number iterator read_next_int to construct own data structure
    void (*start)(FILE* stream);
} SearchAlgorithm;

/*
    Externing different search algorithms to be defined in own separate files]
*/
extern SearchAlgorithm search_best_fit_runner;

// TODO: Rest of algorithms...