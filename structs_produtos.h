#ifndef STRUCTS_PRODUTOS_H
#define STRUCTS_PRODUTOS_H
#include <stdlib.h>

typedef struct list {

    struct produto *head;
    int size;

}List;

typedef struct produto {

    char *nome_prod;
    int codigo_unico;
    int preço;
    int quantidade;
    struct produto *next;

}Produto;

#endif