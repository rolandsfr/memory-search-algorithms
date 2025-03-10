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

    FILE* chunks_fs = open_number_stream_from_file(chunks_file_name);
    FILE* sizes_fs = open_number_stream_from_file(sizes_file_name);

    // print which files are being used and which algorithm bechmarked
    printf("Setting up files:\n - Chunks file: %s\n - Sizes file: %s\n",
        chunks_file_name,
        sizes_file_name
    );

    if(algorithm != NULL) {
        SearchAlgorithm algorithm_runner;
        printf("Using %s algorithm\n", algorithm);

        // TODO: complete with the rest of algorithms when they are done
        if(strcmp(algorithm, "best_fit") == 0) {
            algorithm_runner.start = search_best_fit_runner.start;
        }

        if(strcmp(algorithm, "first_fit") == 0) {
            algorithm_runner.start = search_first_fit_runner.start;
        }

        if(strcmp(algorithm, "next_fit") == 0) {
            algorithm_runner.start = search_next_fit_runner.start;
        }

        if(algorithm_runner.start != NULL) {
            algorithm_runner.start(chunks_fs);
        }

    }

    printf("\n");


    return 0;
}