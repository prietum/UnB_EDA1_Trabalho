#ifndef COMPRAS_H
#define COMPRAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structs_cliente.h"
#include "structs_produtos.h"
#include "structs_compras.h"

// main
ListaCarrinhos* criar_lista_carrinhos();
void destruir_lista_carrinhos(ListaCarrinhos* lista);
Carrinho* criar_carrinho(clienteNode *cl_alvo_ptr);
ItemCarrinho* criar_item_carrinho(int codigo, char* nome, float preco, int quantidade);
int adicionar_ao_carrinho(Carrinho* carrinho, ItemCarrinho* item);
int remover_do_carrinho(Carrinho* carrinho, int codigo_produto);
void limpar_carrinho(Carrinho* carrinho);
void exibir_carrinho(Carrinho* carrinho);
float calcular_total_carrinho(Carrinho* carrinho);
int finalizar_compra(Carrinho* carrinho, List* lista_produtos);
Carrinho* buscar_carrinho_por_cliente(ListaCarrinhos* lista, clienteNode *cl_node_ptr);

// menu
void modo_compra_acesso_menu(List* lista_produtos, Carrinho* carrinho_atual);
void modo_compra_busca_menu(List* lista_produtos, ListaCarrinhos* lista_carrinhos, clienteNode *cl_head_ptr);
void adicionar_produto_carrinho_menu(Carrinho* carrinho, List* lista_produtos);
void remover_produto_carrinho_menu(Carrinho* carrinho);
void listar_carrinho_menu(Carrinho* carrinho);
void finalizar_compra_menu(Carrinho* carrinho, List* lista_produtos);

#endif