#ifndef STRUCTS_COMPRAS_H
#define STRUCTS_COMPRAS_H

#include "cliente.h"

typedef struct item_carrinho 
{
    int codigo_produto;
    char nome_produto[101];
    float preco_unitario;
    int quantidade;
    float subtotal;
    struct item_carrinho* prox;
} ItemCarrinho;

typedef struct carrinho
{
    clienteNode *cl_node_ptr;
    ItemCarrinho* itens;
    int total_itens;
    float valor_total;
    struct carrinho* prox;
} Carrinho;

typedef struct lista_carrinhos
{
    Carrinho* head;
    int size;
} ListaCarrinhos;

#endif