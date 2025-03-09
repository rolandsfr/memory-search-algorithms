#include <algorithms.h>
#include <parsers.h>

void search_best_fit(FILE* stream) {
    int num;

    // TODO: construct binary search tree
    while((num = read_next_int(stream)) != EOF) {
        printf("%d\n", num);
    }
}

SearchAlgorithm search_best_fit_runner = {
    .start = search_best_fit
};

