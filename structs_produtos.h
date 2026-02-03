#ifndef STRUCTS_PRODUTOS_H
#define STRUCTS_PRODUTOS_H

typedef struct produto 
{
    char nome_prod[101];
    int codigo_unico;
    float preco;           
    int quantidade;
    struct produto* prox; 
} Produto;

typedef struct list 
{
    Produto* head;
    int size;
} List;

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
    int cpf_cliente;
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