#include <stdio.h>
#include <cli.h>
#include <algorithms.h>
#include <parsers.h>
#include <string.h>

int main(int argc, char** argv) {
    // parse input
    char* params[PARAMS_COUNT] = {NULL, NULL, NULL};
    parse_input(argc, argv, params);

    // retrieve input file names
    char* chunks_file_name = get_param_value(CHUNKS, params);
    char* sizes_file_name = get_param_value(SIZES, params);
    char* algorithm = get_param_value(ALGO, params);

    ParsedFile* chunks = parse_file(chunks_file_name);
    ParsedFile* sizes = parse_file(sizes_file_name);

    // print which files are being used and which algorithm bechmarked
    printf("Setting up files:\n - Chunks file: %s (%d records)\n - Sizes file: %s (%d records)\n",
        chunks_file_name,
        chunks->size,
        sizes_file_name,
        sizes->size
    );

    if(algorithm != NULL) {
        SearchAlgorithm algorithm_runner;
        printf("Using %s algorithm\n", algorithm);

        // TODO: complete with the rest of algorithms when they are done
        if(strcmp(algorithm, "best_fit") == 0) {
            algorithm_runner.search = search_best_fit_runner.search;
        }

        if(algorithm_runner.search != NULL) {
            algorithm_runner.search(chunks->array, chunks->size, sizes->array, sizes->size);
        }

    }

    printf("\n");


    return 0;
}