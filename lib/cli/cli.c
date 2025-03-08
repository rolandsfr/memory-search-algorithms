#include <stdio.h>
#include <cli.h>
#include <string.h>

int hash_param(char* param_short_name) {
    // hash for chunks param
    if(strcmp(param_short_name, "-c") == 0) return 0;
    // hash for sizes param
    else if(strcmp(param_short_name, "-s") == 0) return 1;
    // default
    return -1;
}

void set_param(char* param_short_name, char* file_name, char** input_files) {
    int hash = hash_param(param_short_name);
    if(hash != -1) {
        input_files[hash] = file_name;
    } else {
        printf("[FATAL]: Unrecognized param: %s\n", param_short_name);
    }
}

// returns 0 for flag not found or else 1
void parse_input(int argc, char** argv, char** input_files) {
    if(argc != 1 + 4) {
        printf("Invalid number of parameters: %d!\n", argc);
        return;
    }

    for (int i = 1; i < argc; i++) {
        char* param_name = argv[i];
        char* param_value = argv[i + 1];
        i++; // skip param value not to be treated as an argument
        set_param(param_name, param_value, input_files);
    }
}

char* get_file_name(FILE_TYPE type, char** input_files) {
    switch(type) {
        case CHUNKS: {
            return input_files[hash_param("-c")];
        }
        case SIZES: {
            return input_files[hash_param("-s")];
        }
        default: {
            return NULL;
        }
    }
}