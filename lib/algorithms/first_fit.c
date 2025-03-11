#include <algorithms.h>
#include <parsers.h>

#define MEM_SIZE 1024

typedef struct MemoryBlock {
  size_t size;
  int is_free;
  int value;
  struct MemoryBlock *next;
} MemoryBlock;

/* It kā vienkāršāk bez saraksta, bet ar statisku masīvu.
Varbū tomēr nē, un piestrādāt pie saraksta */
void search_first_fit(FILE* stream) {
  int num;
  int memory[MEM_SIZE];
  
  /* Inicializējam visu atmiņu kā brīvu */
  for (int i = 0; i < MEM_SIZE; i++) {
    memory[i] = 0;  
  }
  
  /* Nolasām visus pieprasījumus no faila */
  while( (num = read_next_int(stream)) != EOF ) {
    /* Pieņemam, ka katrs skaitlis aizņem int izmēru */
    int size_needed = sizeof(int);  
    int allocated = 0;  
    
    /* FirstFit algoritms - meklējam pirmo pietiekami lielu brīvu vietu */
    for (int i = 0; i <= TOTAL_MEMORY_SIZE - size_needed; i++) {
      /* Pārbaudām, vai atmiņas bloks ir brīvs */
      int free_block = 1;
      for (int j = 0; j < size_needed; j++) {
        if (memory[i + j] != 0) {
          free_block = 0;
          break;
        }
      }
      
      /* Ja atrasts brīvs bloks, piešķiram tam atmiņu */
      if (free_block) {
        for (int j = 0; j < size_needed; j++) {
          memory[i + j] = 1; 
        }
        allocated = 1;
        break;
      }
    }
  }
}

/* Izmanto sarakstu, sarežģīti un hvz, vai strādās */
void search_first_fit_struct(FILE* stream) {
  int num;
  MemoryBlock *head = NULL;
  
  /* Inicializējam atmiņu ar vienu lielu bloku */
  head = (MemoryBlock *)malloc(sizeof(MemoryBlock));
  if (head == NULL) {
    /* Fail to init mem */
    return;
  }
  
  head->size = MEM_SIZE;
  head->is_free = 1;
  head->next = NULL;
  
  while((num = read_next_int(stream)) != EOF) {
    /* FirstFit vienmēr sāk no sākuma */
    MemoryBlock *current = head; 
    int allocated = 0;
    /* Pieņemam, ka katrs skaitlis aizņem int izmēru.
      TODO: Bet varbūt MemoryBlock? 
    */
    int required_size = sizeof(int); 
    
    while (current != NULL) {
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

        allocated = 1;
        break;
      }
      
      current = current->next;
    }

  }
  
  /* Atbrīvojam atmiņu */
  while (head != NULL) {
    MemoryBlock *temp = head;
    head = head->next;
    free(temp);
  }
}

SearchAlgorithm search_first_fit_runner = {
  .start = search_first_fit
};
