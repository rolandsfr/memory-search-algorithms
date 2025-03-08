#include <stdio.h>
#include <stdlib.h>
#include <parsers.h>

#define BUFFER_SIZE 100

ParsedFile* parse_file(const char* file_name) {
    // FIXME: potentially change 100 to cached number of data entries in the file
    int* list = (int*)malloc(BUFFER_SIZE * sizeof(int));
    FILE* file = fopen(file_name, "r");

    if(file == NULL) {
        printf("File %s does not exist!\n", file_name);
        exit(1);
    }

    int num = 0;
    int ch; 
    int size = 0;
    // track number of times memory realocation has happened
    int buffers_used = 1;

    while ((ch = fgetc(file)) != EOF) { 
        // if new line symbol is encountered
        if (ch == 10) {
            // resize list before overflow
            if(size == 100) {
                list = (int*) realloc(list, BUFFER_SIZE * buffers_used * sizeof(int));
            }

            list[size] = num;
            num = 0; 
            size++;
            buffers_used++;
        } else if (ch >= '0' && ch <= '9') {
            num = num * 10 + (ch - '0');
        }
    }

    // handle char before EOF
    if (num != 0) {
        list[size] = num;
        size++;
    }

    fclose(file);

    ParsedFile* parsed_file = (ParsedFile*) malloc(sizeof(ParsedFile));
    parsed_file->array = list;
    parsed_file->size = size;
    return parsed_file;
}