#include <algorithms.h>
#include <parsers.h>

void search_best_fit(FILE* chunks_fs , FILE* sizes_fs) {
    int num;

    // TODO: construct binary search tree
    while((num = read_next_int(chunks_fs)) != EOF) {
        printf("%d\n", num);
    }
}


SearchAlgorithm search_best_fit_runner = {
    .start = search_best_fit
};

