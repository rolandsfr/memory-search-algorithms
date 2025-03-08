typedef struct ParsedFile {
    int* array;
    int size;
} ParsedFile;

ParsedFile* parse_file(const char* file_name);