#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cliente.h"
#include "structs_cliente.h"

int DIAMES[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

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
	// verifica
	if(anoNasc<1900||anoNasc>2026){printf("ano invalido\n"); return NULL;}
	if(mesNasc<1||mesNasc>12){printf("mes invalido\n"); return NULL;}
	if(diaNasc<1||diaNasc>DIAMES[mesNasc]){printf("dia invalido\n"); return NULL;}
	if(tel[0]!='('||tel[3]!=')'||tel[4]!=' '||tel[5]!='9'||tel[10]!='-'||tel[15]!='\0'){printf("tel invalido\n"); return NULL;}
	if(cpf[3]!='.'||cpf[7]!='.'||cpf[11]!='-'||cpf[14]!='\0'){printf("cpf invalido\n"); return NULL;}
	
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

int editaCliente(clienteNode *cl_node_ptr, char nome[80], char email[80], char cpf[15], char tel[16], int diaNasc, int mesNasc, int anoNasc){
	// verifica
	if(anoNasc<1900||anoNasc>2026){printf("ano invalido\n"); return 2;}
	if(mesNasc<1||mesNasc>12){printf("mes invalido\n"); return 2;}
	if(diaNasc<1||diaNasc>DIAMES[mesNasc]){printf("dia invalido\n"); return 2;}
	if(tel[0]!='('||tel[3]!=')'||tel[4]!=' '||tel[5]!='9'||tel[10]!='-'||tel[15]!='\0'){printf("tel invalido\n"); return 2;}
	if(cpf[3]!='.'||cpf[7]!='.'||cpf[11]!='-'||cpf[14]!='\0'){printf("cpf invalido\n"); return 2;}
	
	cliente *cl_ptr = cl_node_ptr->data;
	
	copiaString(cl_ptr->nome, nome, 0);
	copiaString(cl_ptr->email, email, 0);
	copiaString(cl_ptr->cpf, cpf, 0);
	copiaString(cl_ptr->tel, tel, 0);
	cl_ptr->diaNasc = diaNasc;
	cl_ptr->mesNasc = mesNasc;
	cl_ptr->anoNasc = anoNasc;
	
	return 1;
}

int buscaCliente_CPF(clienteBuscaResultado *cl_bus, clienteNode *cl_head_ptr, char cpf[15]){ //retorna 1 se bem sucedido, 0 se erro, 2 se formato esta errado
	if(cpf[3]!='.'||cpf[7]!='.'||cpf[11]!='-'||cpf[14]!='\0')return 2;

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

int buscaCliente_tel(clienteBuscaResultado *cl_bus, clienteNode *cl_head_ptr, char tel[16]){ //retorna 1 se bem sucedido, 0 se nao achou, 2 se formato esta errado
	if(tel[0]!='('||tel[3]!=')'||tel[4]!=' '||tel[5]!='9'||tel[10]!='-'||tel[15]!='\0')return 2;

	clienteNode *cl_tail_ptr = cl_head_ptr;
	clienteNode *cl_tail_prox_ptr = cl_head_ptr->prox;
	int ok = 0;
	
	while (cl_tail_prox_ptr!=NULL&&strcmp(cl_tail_prox_ptr->data->tel, tel)!=0){
		cl_tail_ptr = cl_tail_prox_ptr;
		cl_tail_prox_ptr = cl_tail_prox_ptr->prox;
	}
	
	if (cl_tail_prox_ptr!=NULL){
		cl_bus->ante = cl_tail_ptr;
		cl_bus->alvo = cl_tail_prox_ptr;
		return 1;
	} else return 0;
}

void removeCliente(clienteNode *cl_alvo_ptr, clienteNode *cl_ante_ptr){
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

void destroiListaClientes(clienteNode *cl_head_ptr){ //recursivo
	if (cl_head_ptr->prox!=NULL){
		destroiListaClientes(cl_head_ptr->prox);
	}
	free(cl_head_ptr);
}

///////////////////////////////////////////////////////////////////////

//Baseado em produtos.c

void cria_cliente_menu(clienteNode *cl_head_ptr) {
    int qtd = 0;
    char nome[80];
    char email[80];
	char cpf[15];
	char tel[16];
	int diaNasc;
	int mesNasc;
	int anoNasc;
    int sucessos = 0;
    
    printf("\n>-------- CADASTRO DE CLIENTE --------<\n");
    printf("Quantos clientes serao cadastrados? ");
    scanf("%d", &qtd);
    
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cliente %d/%d ---\n", i + 1, qtd);
        
        printf("Nome do cliente: ");
		getchar();
        //fgets(nome, 80, stdin);
		scanf("%[^\n]", &nome);
        nome[strcspn(nome, "\n")] = '\0';  
        
		printf("E-mail do cliente: ");
		getchar();
        //fgets(email, 80, stdin);
		scanf("%[^\n]", &email);
        email[strcspn(email, "\n")] = '\0';  
		
		printf("CPF do cliente (xxx.xxx.xxx-xx): ");
		getchar();
        //fgets(cpf, 15, stdin);
		scanf("%[^\n]", &cpf);
        cpf[strcspn(cpf, "\n")] = '\0';  
		
		printf("Telefone do cliente ((xx) 9xxxx-xxxx): ");
		getchar();
        scanf("%[^\n]", &tel);
        tel[strcspn(tel, "\n")] = '\0';
		
		//????????????????????????
		scanf("%*[^\n]%*c");
		//????????????????????????
		
        printf("Dia do nascimento: ");
        scanf("%d", &diaNasc);
        
        printf("Mes do nascimento: ");
        scanf("%d", &mesNasc);
        
        printf("Ano do nascimento: ");
        scanf("%d", &anoNasc);
        
		//debug
		//printf("\nnome %s\nemail %s\ncpf %s\ntel %s\nnasc %d / %d / %d\n", nome, email, cpf, tel, diaNasc, mesNasc, anoNasc);
		
        clienteNode *cl_node_ptr = insereCliente(cl_head_ptr, nome, email, cpf, tel, diaNasc, mesNasc, anoNasc);
        if (cl_node_ptr != NULL) {
			printf("Cliente cadastrado com sucesso!\n");
            sucessos++;
        }
    }
    
    printf("\nTotal de clientes cadastrados: %d/%d\n", sucessos, qtd);
}

void acessa_cliente_menu(clienteNode *cl_head_ptr, clienteNode *cl_alvo_ptr, clienteNode *cl_ante_ptr) {
	int opcao_acc;
	
	do {
		printaCliente(cl_alvo_ptr);
		printf("\n");
		printf("1. Editar\n");
		printf("2. Remover\n");
		printf("3. Voltar\n");
		scanf("%d", &opcao_acc);
	
		char nome[80];
		char email[80];
		char cpf[15];
		char tel[16];
		int diaNasc;
		int mesNasc;
		int anoNasc;
	
		switch(opcao_acc){
			case 1:
				printf("\n--- Editando ---\n");
			
				printf("Nome do cliente: ");
				getchar();
				//fgets(nome, 80, stdin);
				scanf("%[^\n]", &nome);
				nome[strcspn(nome, "\n")] = '\0';  
        
				printf("E-mail do cliente: ");
				getchar();
				//fgets(email, 80, stdin);
				scanf("%[^\n]", &email);
				email[strcspn(email, "\n")] = '\0';  
		
				printf("CPF do cliente (xxx.xxx.xxx-xx): ");
				getchar();
				//fgets(cpf, 15, stdin);
				scanf("%[^\n]", &cpf);
				cpf[strcspn(cpf, "\n")] = '\0';  
		
				printf("Telefone do cliente ((xx) 9xxxx-xxxx): ");
				getchar();
				scanf("%[^\n]", &tel);
				tel[strcspn(tel, "\n")] = '\0';
		
				//????????????????????????
				scanf("%*[^\n]%*c");
				//????????????????????????
		
				printf("Dia do nascimento: ");
				scanf("%d", &diaNasc);
        
				printf("Mes do nascimento: ");
				scanf("%d", &mesNasc);
        
				printf("Ano do nascimento: ");
				scanf("%d", &anoNasc);
        
				//debug
				//printf("\nnome %s\nemail %s\ncpf %s\ntel %s\nnasc %d / %d / %d\n", nome, email, cpf, tel, diaNasc, mesNasc, anoNasc);
				
				int edit_ok = editaCliente(cl_alvo_ptr, nome, email, cpf, tel, diaNasc, mesNasc, anoNasc);

				if (edit_ok == 1) {
					printf("Cliente editado com sucesso :)\n");
				} else {
					printf("Erro ao editar cliente :(\n");
				}
				return;
			case 2:
				removeCliente(cl_alvo_ptr, cl_ante_ptr);
				printf("Cliente removido com sucesso!\n");
				return;
			case 3:
				printf("Voltando...\n");
				return;
			default:
				printf("Opcao invalida :(\n");
				break;
		}
	} while (opcao_acc!=3);
}

void busca_cliente_menu(clienteNode *cl_head_ptr) {
    int opcao_bpm;
    
	//armazena resultado de busca
	clienteBuscaResultado *busca = malloc(sizeof(clienteBuscaResultado));
	int busca_ok = 0;
	
    do {
        printf("\n>-------- BUSCA DE CLIENTE --------<\n");
        printf("1. Buscar por CPF\n");
        printf("2. Buscar por telefone\n");
        printf("3. Voltar para gerenciamento de clientes\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao_bpm);
        
        switch(opcao_bpm) {
            case 1: {
                char cpf[15];
                printf("Digite o CPF do cliente (xxx.xxx.xxx-xx): ");
                getchar();
                fgets(cpf, 15, stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                
                busca_ok = buscaCliente_CPF(busca, cl_head_ptr, cpf);
                break;
            }
                
            case 2: {
                char tel[16];
                printf("Digite o telefone do cliente ((xx) 9xxxx-xxxx): ");
                getchar();
                fgets(tel, 16, stdin);
                tel[strcspn(tel, "\n")] = '\0';
                
                busca_ok = buscaCliente_tel(busca, cl_head_ptr, tel);
                break;
            }
                
            case 3:
                printf("Voltando...\n");
                return;
                
            default:
                printf("Opcao invalida :(\n");
                break;
        }
        
		if (busca_ok == 1) {
			printf("\n>-------- CLIENTE ENCONTRADO --------<\n");
			acessa_cliente_menu(cl_head_ptr, busca->alvo, busca->ante);
		} else if (busca_ok == 0) {
			printf("Cliente nao encontrado!\n");
		} else if (busca_ok == 2) {
			if (opcao_bpm == 1) {
				printf("CPF digitado incorretamente!\n");
			} else if (opcao_bpm == 2) {
				printf("Telefone digitado incorretamente!\n");
			}
		}
		
        if (opcao_bpm != 3) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
    } while (opcao_bpm != 3);
}

///////////////////////////////////////////////////////////////////////

int main_cliente(clienteNode *cl_head_ptr){
	//baseado em produtos.c
	int opcao_main_cliente = 0;
    
    do {
        printf("\n>-------- GERENCIAMENTO DE CLIENTES --------<\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar clientes cadastrados\n");
        printf("3. Acessar cliente\n");
        printf("4. Voltar para menu principal\n");
        printf("5. Sair da aplicacao\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao_main_cliente);
        
        switch(opcao_main_cliente) {
            case 1:
                cria_cliente_menu(cl_head_ptr);
                break;
            case 2:
                printaListaClientes(cl_head_ptr);
                break;
            case 3:
                busca_cliente_menu(cl_head_ptr);
                break;
            case 4:
                printf("Voltando para menu principal...\n");
                return 0;  // juntar isso na vers final com main
            case 5:
                destroiListaClientes(cl_head_ptr);
                return 1;  // sair do terminal
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
        
        if (opcao_main_cliente != 4 && opcao_main_cliente != 5) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while (opcao_main_cliente != 4 && opcao_main_cliente != 5);
    
    return (opcao_main_cliente == 5) ? 1 : 0;
}