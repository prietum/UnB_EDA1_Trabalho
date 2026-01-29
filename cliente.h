#include <string.h>

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

int createCliente(struct clienteCelula *le, struct clienteStruct *cliente){
	struct clienteCelula *add;
	add->cliente = cliente;
	add->prox = NULL;

	struct clienteCelula *ult = getLastCliente(le);
	if (ult != NULL) ult->prox = add;
	
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

//TODO
//ADICIONAR FUNCAO QUE PRINTA A LISTA ENCADEADA
