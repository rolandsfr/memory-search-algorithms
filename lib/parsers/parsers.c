#include <stdio.h>
#include <stdlib.h>
#include <parsers.h>

ParsedFile* parse_file(const char* file_name) {
    // FIXME: potentially change 100 to cached number of data entries in the file
    int* list = (int*)malloc(100* sizeof(int));
    FILE* file = fopen(file_name, "r");

    int num = 0;
    int ch; 
    int size = 0;

    while ((ch = fgetc(file)) != EOF) { 
        // if new line symbol is encountered
        if (ch == 10) {
            list[size] = num;
            num = 0; 
            size++;
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