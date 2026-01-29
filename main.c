#include "cliente.h"
#include <stdio.h>
int main(){
	struct clienteCelula *le; //LISTA ENCADEADA
	
	//teste
	struct dataNascimento nasc = {
		.dia = 20,
		.mes = 4,
		.ano = 1999
	};
	struct clienteStruct c = {
		.nome = "silva da silva",
		.cpf = "12312312345",
		.nasc = nasc,
		.email = "silva@gmail.com",
		.telefone = "61912341234"
	};
	addCliente(le, &c);
}
