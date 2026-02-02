#include "cliente.h"
#include <stdio.h>
int main(){
	struct clienteCelula *le; //LISTA ENCADEADA
	
	//teste
	struct clienteStruct *c = malloc(sizeof(struct clienteStruct));
	if (c!=NULL){
		c->nome = "silva da silva";
		c->cpf = "12312312345";
		c->email = "silva@gmail.com";
		c->tel = "61912341234";
		struct dataNascimento *n = malloc(sizeof(struct dataNascimento));
		if (n!=NULL){
			n->dia = 20;
			n->mes = 6;
			n->ano = 1999;
			c->nasc = n;
		}
	}

	printf("adicionando cliente");
	addCliente(le, c);
	printf("printando cliente");
	printClientes(le);
}
