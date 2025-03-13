/*

Vispirms izveidot vienu lielu brīvu bloku, kas atbilst izdalītai kopējai atmiņai.
Meklējot brīv vietu skaitlim, pārbauda, vai ir pietiekami liels brīvs bloks.
Ja ir, tad ievieto skaitli šajā blokā.
Ja brīvs bloks ir lielāks nekā nepieciešams, tad sadala bloku divos blokos - vienu skaitlim, otru atstāj brīvu.
Ja brīvs bloks ir mazāks nekā nepieciešams, tad meklē nākamo brīvo bloku.
Ja nav brīva bloka, tad atgriež kļūdu.

*/
#include <algorithms.h>
#include <parsers.h>

/* Pieņemt, ka izdalītās atmiņas kopējais apjoms ir 1024 baiti. */
#define MEM_SIZE 1024 

unsigned char mybuffer_nextfit[MEM_SIZE];
size_t next_fit_index = 0;

void *nextfit_alloc(size_t size) {
  size_t start_index;
  size_t free_space;
  size_t alloc_start;
  size_t i;

  if (size == 0 || size > MEM_SIZE) {
    return NULL;
  }

  start_index = next_fit_index;
  free_space = 0;

  while (free_space < size) {
    if (mybuffer_nextfit[next_fit_index] == 0) {
      free_space++;
    } else {
      free_space = 0;
    }

    next_fit_index = (next_fit_index + 1) % MEM_SIZE;

    if (next_fit_index == start_index) {
      return NULL;
    }
  }

  alloc_start = (next_fit_index + MEM_SIZE - free_space) % MEM_SIZE;
  for (i = 0; i < size; i++) {
    mybuffer_nextfit[alloc_start + i] = 1;
  }

  next_fit_index = (alloc_start + size) % MEM_SIZE;
  return &mybuffer_nextfit[alloc_start];
}

void search_next_fit(FILE* stream) {
  int num;

  while ( (num = read_next_int(stream)) != EOF) {
    /* void *ptr = nextfit_alloc(sizeof(int)); */
    void *ptr = nextfit_alloc(MEM_SIZE);
    if (ptr != NULL) {
      /* printf("[ INFO ] Allocated %lu bytes at address %p\n", sizeof(int), ptr); */
      printf("[ INFO ] Allocated %lu bytes at address %p\n", (unsigned long)MEM_SIZE, ptr);
    } else {
      /* printf("[ ERROR ] Failed to allocate %lu bytes\n", sizeof(int)); */
      printf("[ ERROR ] Failed to allocate %lu bytes\n", (unsigned long)MEM_SIZE);
    }
  }
}

SearchAlgorithm search_next_fit_runner = {
  .start = search_next_fit
};
