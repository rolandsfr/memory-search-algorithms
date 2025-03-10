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

typedef struct MemoryBlock {
  size_t size;
  int is_free;
  int value;
  struct MemoryBlock* next;
} MemoryBlock;

void search_next_fit(FILE* stream) {
  int num;
  MemoryBlock *head = NULL;
  MemoryBlock *last_allocation = NULL;

  /* Init mem */
  head = (MemoryBlock *)malloc(sizeof(MemoryBlock));
  if (head == NULL) {
    /* Fail to init mem */
    return;
  }
  
  head->size = MEM_SIZE;
  head->is_free = 1;
  head->next = NULL;

  /* Start from the beginning */
  last_allocation = head; 

  while ( (num = read_next_int(stream)) != EOF) {
    MemoryBlock *current = last_allocation;
    MemoryBlock *start = last_allocation;
    int wrapped = 0;
    int allocated = 0;
    /* Pieņemam, ka katrs skaitlis aizņem int izmēru.
      TODO: Bet varbūt MemoryBlock? 
    */
    int required_size = sizeof(int);

    while (1) {
      /* Ja ir brīva vieta un pietiekami liela, lai ievietotu skaitli */
      if (current->is_free && current->size >= required_size) {
        /* Ja atrastais bloks ir lielāks nekā nepieciešams, tad to sadala
        */
        if (current->size > required_size + sizeof(MemoryBlock)) {
          MemoryBlock *new_block =  (MemoryBlock *)(
                                        (char *)current + 
                                        sizeof(MemoryBlock) + 
                                        required_size);

          new_block->size = current->size - required_size - sizeof(MemoryBlock);
          new_block->is_free = 1;
          new_block->next = current->next;
          
          current->size = required_size;
          current->next = new_block;
        }

      current->is_free = 0;
      current->value = num;
      /* Atjauno pēdējo alloc vietu */
      last_allocation = current; 
      allocated = 1;
      break;
    }

    current = current->next;

    /* Ja ir saraksta beigās, tad atpakaļ uz sākumu */
    if (current == NULL) {
      current = head;
      wrapped = 1;
    }

    /* Apiets pilns aplis un atpakaļ sākuma punktā */
    if (wrapped && current == start) {
      break;
    }
  }

  /* Tīrīt atmiņu */
  while (head != NULL) {
    MemoryBlock *tmp = head;
    head = head->next;
    free(tmp);
  }

}

SearchAlgorithm search_next_fit_runner = {
  .start = search_next_fit
};
