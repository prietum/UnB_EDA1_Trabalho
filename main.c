#include "cliente.h"
#include <stdio.h>
int main(){
	//LISTA ENCADEADA
	clienteNode *cl_head_ptr = criaListaClientes();
	
	//teste
	insereCliente(cl_head_ptr, "silva da silva", "silvadasilva@gmail.com", "123.456.789-20", "(61) 91234-5678", 20, 12, 1999);
	insereCliente(cl_head_ptr, "souza de souza", "souzadesouza@gmail.com", "999.888.777-13", "(45) 96666-1234", 1, 7, 2025);
	insereCliente(cl_head_ptr, "lima lima", "limalima@gmail.com", "011.022.033-44", "(30) 98767-1000", 15, 3, 1930);
	insereCliente(cl_head_ptr, "pedro rocha", "pedroso@gmail.com", "111.222.333-56", "(10) 95324-6544", 3, 11, 1956);
	insereCliente(cl_head_ptr, "franscisca francis", "franz@gmail.com", "901.555.345-01", "(31) 97283-9958", 31, 12, 2050);
	
	printaListaClientes(cl_head_ptr);
	
	//Procedimento de finalização
	printf("Programa terminado!\n");
	system("pause");
	return 0;
}
