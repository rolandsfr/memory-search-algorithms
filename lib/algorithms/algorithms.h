/* 
    SearchAlgorithm struct for virtual function definition
*/
typedef struct SearchAlgorithm {
    // search algorithms returns nothing as soon as appropriate chunk is found
    // it accepts dynamic array of chunks as integers and dynamic array of sizes as integers for each to find a chunk for
    void (*search)(int* chunks, int* sizes);
} SearchAlgorithm;

/*
    Externing different search algorithms to be defined in own separate files]
*/

// Best fit algorithm
extern SearchAlgorithm search_best_fit_runner;

// TODO: Rest of algorithms...