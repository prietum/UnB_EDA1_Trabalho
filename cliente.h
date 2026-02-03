#ifndef CLIENTE_H
#define CLIENTE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct cliente;
struct clienteNode;
struct clienteBuscaResultado;

void copiaString(char *dest, char *ori, int i);
struct clienteNode * criaListaClientes();
struct clienteNode * insereCliente(struct clienteNode *cl_head_ptr, char nome[80], char email[80], char cpf[15], char tel[16], int diaNasc, int mesNasc, int anoNasc);
void editaCliente(struct clienteNode *cl_node_ptr, char nome[80], char email[80], char cpf[15], char tel[16], int diaNasc, int mesNasc, int anoNasc);
int buscaCliente_CPF(struct clienteBuscaResultado *cl_bus, struct clienteNode *cl_head_ptr, char cpf[15]);
void removeCliente(struct clienteNode *cl_ante_ptr, struct clienteNode *cl_alvo_ptr);
void printaCliente(struct clienteNode *cl_node_ptr);
void printaListaClientes(struct clienteNode *cl_head_ptr);

#endif