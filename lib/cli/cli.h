#define PARAMS_COUNT 3

typedef enum PARAM {
    CHUNKS,
    SIZES,
    ALGO
} FILE_TYPE;

void parse_input(int argc, char** argv, char** input_files);
char* get_param_value(enum PARAM param, char** params);