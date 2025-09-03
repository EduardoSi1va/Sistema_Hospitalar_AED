#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "item.h"

struct item{ 
        int chave;
        /*outros componentes*/
};

ITEM *item_criar (int chave){
          ITEM *item;
          
          item = (ITEM *) malloc(sizeof(ITEM));
          
          if (item != NULL){
             item->chave = chave;
             return(item);
          }
          return(NULL);
}

bool item_apagar(ITEM **item){
   if (*item != NULL){
      free (*item); // Free apenas marca o espaço de memória como disponível
      *item = NULL; // Limpa o valor do espaço, pois o ponteiro recebe NULL
      return(true);
   }
   return(false);
}

int item_get_chave(ITEM *item){
    if (item != NULL)
      return(item->chave);
    exit(1);
}


bool item_set_chave(ITEM *item, int chave){
  if (item != NULL){
    item->chave = chave;
    return (true);
  }
  return (false);
}

void item_imprimir(ITEM *item){
     if (item != NULL){
        printf("\n-->item chave: %d\n", item->chave);
     }
}