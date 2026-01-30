#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct dataNascimento {
	int dia;
	int mes;
	int ano;
};

struct clienteStruct {
	char nome[80];
	char email[80];
	struct dataNascimento nasc;
	char cpf[12];
	char tel[12]; 
};

struct clienteCelula {
	struct clienteStruct *cliente;
	struct clienteCelula *prox;
};

struct clienteCelula *getLastCliente(struct clienteCelula *le){
	struct clienteCelula *p = le;
	while (p != NULL && p->prox != NULL)
		p = p->prox;
	printf("pega ultimo cliente");
	return p;
}

struct clienteCelula *getClienteOfIndex(struct clienteCelula *le, int i){
	struct clienteCelula *p = le;
	while(p!=NULL&&i>0){
		i--;
		p = p->prox;
	}
	return p;
}

struct clienteCelula *getClienteOfCPF(struct clienteCelula *le, char cpf[12]){
	struct clienteCelula *p = le;
	while(p!=NULL&&strcmp(p->cliente->cpf, cpf)==1){
		p = p->prox;
	}
	return p;
}

int addCliente(struct clienteCelula *le, struct clienteStruct *cliente){
	printf("fazendo nova celula\n");
	struct clienteCelula addCel;
	addCel.cliente = malloc(sizeof(struct clienteStruct));
	printf("ok1\n");
	printf("%p, %p\n", addCel.cliente, cliente);
	addCel.cliente = cliente;
	printf("ok2\n");
	addCel.prox = NULL;
	printf("fez nova celula\n");

	//TODO usar malloc ou algo
	struct clienteCelula *add = &addCel;
	printf("fez nova celula ptr\n");

	struct clienteCelula *ult = getLastCliente(le);
	if (ult != NULL) ult->prox = add;
	printf("sucesso\n");
	
	return 0; //sucesso
}

int removeCliente(struct clienteCelula *le, int i){
	struct clienteCelula *r = le;
	struct clienteCelula *anterior = NULL;
	while(r!=NULL&&i>0){
		i--;
		anterior = r;
		r = r->prox;
	}
	struct clienteCelula *posterior = r->prox;
	if(anterior!=NULL){
		anterior->prox = posterior;
	}

}

void printClientes(struct clienteCelula *le){
	struct clienteCelula *p = le;
	printf("Clientes:\n");
	while (p!=NULL) {
		struct clienteStruct *c = p->cliente;
		printf("\t%s\n\tCPF: %s\n\tE-mail: %s\n\tTelefone: %s\n\tNascido(a) em %d/%d/%d\n\n", c->nome, c->cpf, c->email, c->tel, c->nasc.dia, c->nasc.mes, c->nasc.ano);
		p = p->prox;
	}
}
