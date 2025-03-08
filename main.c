#include <stdio.h>
#include <cli.h>
#include <algorithms.h>
#include <parsers.h>

int main(int argc, char** argv) {
    // parse input
    char* input_files[2];
    parse_input(argc, argv, input_files);

    // retrieve input file names
    char* chunks_file_name = get_file_name(CHUNKS, input_files);
    char* sizes_file_name = get_file_name(SIZES, input_files);

    ParsedFile* chunks = parse_file(chunks_file_name);
    ParsedFile* sizes = parse_file(sizes_file_name);

    // print which files are being used
    printf("Setting up files:\n - Chunks file: %s (%d records)\n - Sizes file: %s (%d records)\n",
        chunks_file_name,
        chunks->size,
        sizes_file_name,
        sizes->size
    );

    search_best_fit_runner.search(chunks->array, chunks->size, sizes->array, sizes->size);

    return 0;
}