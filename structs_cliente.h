#ifndef STRUCTS_CLIENTE_H
#define STRUCTS_CLIENTE_H

typedef struct cliente{
	char nome[80];
	char email[80];
	char cpf[15];
	char tel[16]; 
	int diaNasc;
	int mesNasc;
	int anoNasc;
} cliente;

typedef struct clienteNode{
	cliente *data;
	struct clienteNode *prox;
} clienteNode;

typedef struct clienteBuscaResultado{
	clienteNode *ante;
	clienteNode *alvo;
} clienteBuscaResultado;

#endif