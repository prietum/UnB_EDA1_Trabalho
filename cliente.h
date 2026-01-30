#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char nome[80];
	char email[80];
	char cpf[20];
	char tel[20]; 
	int diaNasc;
	int mesNasc;
	int anoNasc;
} cliente;

typedef struct clienteNode{
	cliente *data;
	struct clienteNode *prox;
} clienteNode;

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

void insereCliente(clienteNode *cl_head_ptr, char nome[80], char email[80], char cpf[15], char tel[15], int diaNasc, int mesNasc, int anoNasc){
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
	clienteNode *nd_ptr = malloc(sizeof(clienteNode));
	nd_ptr->data = cl_ptr;
	nd_ptr->prox = NULL;
	
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
	
	cl_tail_ptr->prox = nd_ptr;
	
	//debug
	cliente cl = *cl_ptr
	
	printf("Debug 'cliente'\n");
	printf("Nome: %s -> ", nome); printf("%s | %s\n", cl.nome, nd_ptr->data->nome);
	printf("E-mail: %s -> ", email); printf("%s | %s\n", cl.email, nd_ptr->data->email);
	printf("Cpf: %s -> ", cpf); printf("%s | %s\n", cl.cpf, nd_ptr->data->cpf);
	printf("Tel.: %s -> ", tel); printf("%s | %s\n", cl.tel, nd_ptr->data->tel);
	printf("Dia: %d -> ", diaNasc); printf("%d | %d\n", cl.diaNasc, nd_ptr->data->diaNasc);
	printf("Mês: %d -> ", mesNasc); printf("%d | %d\n", cl.mesNasc, nd_ptr->data->mesNasc);
	printf("Ano: %d -> ", anoNasc); printf("%d | %d\n", cl.anoNasc, nd_ptr->data->anoNasc);
	
	//printf("Debug 'clienteNode'\n");
	//printf("Ponteiro 'cl_ptr': %p, alocado %d bytes.\n", cl_ptr, sizeof(cl_ptr));
	//printf("Ponteiro 'nd_ptr': %p, alocado %d bytes.\n", nd_ptr, sizeof(nd_ptr));
}

void printaCliente(cliente cl){
	printf("\"%s\"\nE-mail: %s\nCPF: %s\nTelefone: %s\nNascido em %d/%d/%d\n\n",
		cl.nome, cl.email, cl.cpf, cl.tel, cl.diaNasc, cl.mesNasc, cl.anoNasc
	);
}

void printaListaClientes(clienteNode *cl_head_ptr){
	clienteNode *cl_tail_ptr, *cl_tail_prox_ptr;
	cl_tail_ptr = cl_head_ptr;
	cl_tail_prox_ptr = cl_head_ptr->prox;
	
	while (cl_tail_prox_ptr!=NULL){
		cl_tail_ptr = cl_tail_prox_ptr;
		cl_tail_prox_ptr = cl_tail_prox_ptr->prox;
		
		cliente cl = *(cl_tail_ptr->data);
		printaCliente(cl);
		
		//printf("Client Tail Pointer: %p\n", cl_tail_ptr);
		//printf("Client Tail Next Pointer: %p\n", cl_tail_ptr->prox);
	}
}