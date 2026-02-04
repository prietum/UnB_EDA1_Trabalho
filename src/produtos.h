#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

// seclaração da lista 
typedef struct produto Produto;
typedef struct list List;

// declaração de funções
List* criar_lista();
void destruir_lista(List* lista);
Produto* criar_produto(char* nome, int codigo, float preco, int quantidade);
int cadastrar_produto(List* lista, Produto* novo_produto);
void listar_produtos(List* lista);
Produto* buscar_produto_por_codigo(List* lista, int codigo);
Produto* buscar_produto_por_nome(List* lista, char* nome);
int editar_produto(List* lista, int codigo, Produto* novos_dados);
int remover_produto(List* lista, int codigo);
int lista_vazia(List* lista);

// Menu de funções aqui
void cad_produto_menu(List* lista);
void list_produto(List* lista);
void busc_produto_menu(List* lista);
void edit_produto_menu(List* lista);
void remov_produto_menu(List* lista);
int main_produtos(List* lista); 

#endif