#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cliente.h"
#include "structs_cliente.h"

void copiaString(char *dest, char *ori, int i){
	dest[i] = ori[i];
	if (dest[i] == '\0') {
		return;
	}
	i++;
	copiaString(dest, ori, i);
}

clienteNode * criaListaClientes(){
	clienteNode *cl_head_ptr;
	cl_head_ptr = malloc(sizeof(clienteNode));
	cl_head_ptr->prox = NULL;
	return cl_head_ptr;
}

clienteNode * insereCliente(clienteNode *cl_head_ptr, char nome[80], char email[80], char cpf[15], char tel[16], int diaNasc, int mesNasc, int anoNasc){
	// cria o cliente
	cliente *cl_ptr = malloc(sizeof(cliente));
	copiaString(cl_ptr->nome, nome, 0);
	copiaString(cl_ptr->email, email, 0);
	copiaString(cl_ptr->cpf, cpf, 0);
	copiaString(cl_ptr->tel, tel, 0);
	cl_ptr->diaNasc = diaNasc;
	cl_ptr->mesNasc = mesNasc;
	cl_ptr->anoNasc = anoNasc;
	
	// cria o nódulo
	clienteNode *cl_node_ptr = malloc(sizeof(clienteNode));
	cl_node_ptr->data = cl_ptr;
	cl_node_ptr->prox = NULL;
	
	// encontra a cauda
	//printf("Client Head Pointer: %p\n", cl_head_ptr);
	//printf("Client Head Next Pointer: %p\n", cl_head_ptr->prox);
	
	clienteNode *cl_tail_ptr, *cl_tail_prox_ptr;
	cl_tail_ptr = cl_head_ptr;
	cl_tail_prox_ptr = cl_head_ptr->prox;
	while (cl_tail_prox_ptr!=NULL){
		cl_tail_ptr = cl_tail_prox_ptr;
		cl_tail_prox_ptr = cl_tail_prox_ptr->prox;
		//printf("Client Tail Pointer: %p\n", cl_tail_ptr);
		//printf("Client Tail Next Pointer: %p\n", cl_tail_ptr->prox);
	}
	
	cl_tail_ptr->prox = cl_node_ptr;
	
	//debug
	cliente cl = *cl_ptr;
	
	//printf("Debug 'cliente'\n");
	//printf("Nome: %s -> ", nome); printf("%s | %s\n", cl.nome, cl_node_ptr->data->nome);
	//printf("E-mail: %s -> ", email); printf("%s | %s\n", cl.email, cl_node_ptr->data->email);
	//printf("Cpf: %s -> ", cpf); printf("%s | %s\n", cl.cpf, cl_node_ptr->data->cpf);
	//printf("Tel.: %s -> ", tel); printf("%s | %s\n", cl.tel, cl_node_ptr->data->tel);
	//printf("Dia: %d -> ", diaNasc); printf("%d | %d\n", cl.diaNasc, cl_node_ptr->data->diaNasc);
	//printf("Mês: %d -> ", mesNasc); printf("%d | %d\n", cl.mesNasc, cl_node_ptr->data->mesNasc);
	//printf("Ano: %d -> ", anoNasc); printf("%d | %d\n", cl.anoNasc, cl_node_ptr->data->anoNasc);
	
	//printf("Debug 'clienteNode'\n");
	//printf("Ponteiro 'cl_ptr': %p, alocado %d bytes.\n", cl_ptr, sizeof(cl_ptr));
	//printf("Ponteiro 'cl_node_ptr': %p, alocado %d bytes.\n", cl_node_ptr, sizeof(cl_node_ptr));
	
	return cl_node_ptr;
}

void editaCliente(clienteNode *cl_node_ptr, char nome[80], char email[80], char cpf[15], char tel[16], int diaNasc, int mesNasc, int anoNasc){
	cliente *cl_ptr = cl_node_ptr->data;
	
	copiaString(cl_ptr->nome, nome, 0);
	copiaString(cl_ptr->email, email, 0);
	copiaString(cl_ptr->cpf, cpf, 0);
	copiaString(cl_ptr->tel, tel, 0);
	cl_ptr->diaNasc = diaNasc;
	cl_ptr->mesNasc = mesNasc;
	cl_ptr->anoNasc = anoNasc;
}

int buscaCliente_CPF(clienteBuscaResultado *cl_bus, clienteNode *cl_head_ptr, char cpf[15]){ //retorna 1 se bem sucedido, 0 se erro
	clienteNode *cl_tail_ptr = cl_head_ptr;
	clienteNode *cl_tail_prox_ptr = cl_head_ptr->prox;
	int ok = 0;
	
	while (cl_tail_prox_ptr!=NULL&&strcmp(cl_tail_prox_ptr->data->cpf, cpf)!=0){
		cl_tail_ptr = cl_tail_prox_ptr;
		cl_tail_prox_ptr = cl_tail_prox_ptr->prox;
	}
	
	if (cl_tail_prox_ptr!=NULL){
		cl_bus->ante = cl_tail_ptr;
		cl_bus->alvo = cl_tail_prox_ptr;
		return 1;
	} else return 0;
}

void removeCliente(clienteNode *cl_ante_ptr, clienteNode *cl_alvo_ptr){
	cl_ante_ptr->prox = cl_alvo_ptr->prox;
	free(cl_alvo_ptr);
}

void printaCliente(clienteNode *cl_node_ptr){
	cliente *cl_ptr = cl_node_ptr->data;
	printf("\"%s\"\nE-mail: %s\nCPF: %s\nTelefone: %s\nNascido em %d/%d/%d\nEndereco: %p -> %p\n\n",
		cl_ptr->nome, cl_ptr->email, cl_ptr->cpf, cl_ptr->tel, cl_ptr->diaNasc, cl_ptr->mesNasc, cl_ptr->anoNasc, cl_node_ptr, cl_node_ptr->prox
	);
}

void printaListaClientes(clienteNode *cl_head_ptr){
	clienteNode *cl_tail_ptr, *cl_tail_prox_ptr;
	cl_tail_ptr = cl_head_ptr;
	cl_tail_prox_ptr = cl_head_ptr->prox;
	
	printf("###Lista de Clientes:\n");
	while (cl_tail_prox_ptr!=NULL){
		cl_tail_ptr = cl_tail_prox_ptr;
		cl_tail_prox_ptr = cl_tail_prox_ptr->prox;
		
		printaCliente(cl_tail_ptr);
		
		//printf("Client Tail Pointer: %p\n", cl_tail_ptr);
		//printf("Client Tail Next Pointer: %p\n", cl_tail_ptr->prox);
	}
	//printf("\n");
}