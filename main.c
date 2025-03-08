#include <stdio.h>
#include <cli.h>
#include <algorithms.h>

int main(int argc, char** argv) {
    // parse input
    char* input_files[2];
    parse_input(argc, argv, input_files);

    // retrieve input file names
    char* chunks_file_name = get_file_name(CHUNKS, input_files);
    char* sizes_file_name = get_file_name(SIZES, input_files);

    printf("Chunks file: %s\n Sizes file: %s\n", chunks_file_name, sizes_file_name);

    return 0;
}