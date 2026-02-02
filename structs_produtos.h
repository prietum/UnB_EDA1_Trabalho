#ifndef STRUCTS_PRODUTOS_H
#define STRUCTS_PRODUTOS_H

typedef struct produto {
    char nome_prod[101];
    int codigo_unico;
    float preco;           
    int quantidade;
    struct produto* prox; 
} Produto;

typedef struct list {
    Produto* head;
    int size;
} List;

#endif