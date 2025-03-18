#include <stdio.h>
#include <stdlib.h>

int read_next_int(FILE* stream) {
    long int num = 0;
    long int ch; 


    while ((ch = fgetc(stream)) != EOF) { 
        // if new line symbol is encountered, break the loop and return the accumulated number
        if(ch == '\n') {
            return num;
        }

        /* unused, commented out because of debugger error 
        int digit = ch - '0'; */

        if(ch >= '0' && ch <= '9') {
            // parse the number from a char type and merge with what's currently accumulated in the line that is being read from file stream
            num = num * 10 + (ch - '0');
        }
    }

    return (num == 0) ? EOF : num;

}

FILE* open_number_stream_from_file(char* file_name) {
    return fopen(file_name, "r");
}