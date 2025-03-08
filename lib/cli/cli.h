typedef enum FILE_TYPE {
    CHUNKS,
    SIZES
} FILE_TYPE;

void parse_input(int argc, char** argv, char** input_files);
char* get_file_name(FILE_TYPE type, char** input_files);