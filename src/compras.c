#include <stdio.h>
#include <stdlib.h>
#include "compras.h"
#include "cliente.h"
#include "produtos.h"


ListaCarrinhos* criar_lista_carrinhos() {
    ListaCarrinhos* lista = (ListaCarrinhos*)malloc(sizeof(ListaCarrinhos));
    if (lista == NULL) {
        printf("Erro alocando memoria pra lista de carrinhos :(\n");
        return NULL;
    }
    lista->head = NULL;
    lista->size = 0;
    return lista;
}


void destruir_lista_carrinhos(ListaCarrinhos* lista) {
    if (lista == NULL) return;
    
    Carrinho* atual = lista->head;
    while (atual != NULL) {
        Carrinho* temp = atual;
        atual = atual->prox;
        limpar_carrinho(temp);
        free(temp);
    }
    free(lista);
}


Carrinho* criar_carrinho(clienteNode *cl_alvo_ptr) {
    Carrinho* novo = (Carrinho*)malloc(sizeof(Carrinho));
    if (novo == NULL) {
        printf("Erro ao criar carrinho!\n");
        return NULL;
    }
    
    novo->cl_node_ptr = cl_alvo_ptr;
    novo->itens = NULL;
    novo->total_itens = 0;
    novo->valor_total = 0.0;
    novo->prox = NULL;
    
    return novo;
}


ItemCarrinho* criar_item_carrinho(int codigo, char* nome, float preco, int quantidade) {
    ItemCarrinho* novo = (ItemCarrinho*)malloc(sizeof(ItemCarrinho));
    if (novo == NULL) {
        printf("Erro ao criar item do carrinho!\n");
        return NULL;
    }
    
    novo->codigo_produto = codigo;
    strncpy(novo->nome_produto, nome, 100);
    novo->nome_produto[100] = '\0';
    novo->preco_unitario = preco;
    novo->quantidade = quantidade;
    novo->subtotal = preco * quantidade;
    novo->prox = NULL;
    
    return novo;
}


int adicionar_ao_carrinho(Carrinho* carrinho, ItemCarrinho* item) {
    if (carrinho == NULL || item == NULL) {
        return 0;
    }

    ItemCarrinho* atual = carrinho->itens;
    while (atual != NULL) {
        if (atual->codigo_produto == item->codigo_produto) {
            //se existe atual. quantidade
            atual->quantidade += item->quantidade;
            atual->subtotal = atual->preco_unitario * atual->quantidade;
            free(item);
            carrinho->valor_total = calcular_total_carrinho(carrinho);
            return 1;
        }
        atual = atual->prox;
    }
    

    item->prox = carrinho->itens;
    carrinho->itens = item;
    carrinho->total_itens++;
    carrinho->valor_total = calcular_total_carrinho(carrinho);
    
    return 1;
}


int remover_do_carrinho(Carrinho* carrinho, int codigo_produto) {
    if (carrinho == NULL || carrinho->itens == NULL) {
        return 0;
    }
    
    ItemCarrinho* atual = carrinho->itens;
    ItemCarrinho* anterior = NULL;
    
    // Buscar coisa.
    while (atual != NULL && atual->codigo_produto != codigo_produto) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        return 0; 
    }
    
    // Remover 
    if (anterior == NULL) {
        carrinho->itens = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    
    free(atual);
    carrinho->total_itens--;
    carrinho->valor_total = calcular_total_carrinho(carrinho);
    
    return 1;
}


void limpar_carrinho(Carrinho* carrinho) {
    if (carrinho == NULL) return;
    
    ItemCarrinho* atual = carrinho->itens;
    while (atual != NULL) {
        ItemCarrinho* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    
	carrinho->cl_node_ptr = NULL; // assim?
    carrinho->itens = NULL;
    carrinho->total_itens = 0;
    carrinho->valor_total = 0.0;
}


void exibir_carrinho(Carrinho* carrinho) {
    if (carrinho == NULL) {
        printf("Carrinho invalido!\n");
        return;
    }
    
    printf("--------CARRINHO DE COMPRAS--------\n");
    printf("Cliente (CPF): %s\n", carrinho->cl_node_ptr->data->cpf);
    printf("Total de itens: %d\n", carrinho->total_itens);
    printf("\n");
    
    if (carrinho->itens == NULL) {
        printf("Carrinho vazio!\n");
    } else {
        printf("CODIGO | PRODUTO                 | QUANTIDADE | PRECO UNIT. | SUBTOTAL\n");
        printf("-------|-------------------------|------------|-------------|------------\n");
        
        ItemCarrinho* atual = carrinho->itens;
        while (atual != NULL) {
            printf("%-6d | %-23s | %-10d | R$%-9.2f | R$%-9.2f\n",
                   atual->codigo_produto,
                   atual->nome_produto,
                   atual->quantidade,
                   atual->preco_unitario,
                   atual->subtotal);
            atual = atual->prox;
        }
        
        printf("-------|-------------------------|------------|-------------|------------\n");
        printf("                                               TOTAL: R$ %-9.2f\n", carrinho->valor_total);
    }
    printf("----------------------------------------\n");
}

void exibir_lista_carrinhos(ListaCarrinhos* lista){
	if (lista == NULL) return;
	Carrinho* atual = lista->head;
	
	printf("--------CARRINHOS CADASTRADOS--------\n");
	
	while (atual != NULL) {
        exibir_carrinho(atual);
        atual = atual->prox;
    }
}

float calcular_total_carrinho(Carrinho* carrinho) {
    if (carrinho == NULL) return 0.0;
    
    float total = 0.0;
    ItemCarrinho* atual = carrinho->itens;
    
    while (atual != NULL) {
        total += atual->subtotal;
        atual = atual->prox;
    }
    
    return total;
}


Carrinho* buscar_carrinho_por_cliente(ListaCarrinhos* lista, clienteNode *cl_alvo_ptr) {
    if (lista == NULL) return NULL;
    
    Carrinho* atual = lista->head;
    while (atual != NULL) {
        if (atual->cl_node_ptr == cl_alvo_ptr) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return NULL;
}

// confirma compra (atualizar lista base)
int finalizar_compra(Carrinho* carrinho, List* lista_produtos) {
    if (carrinho == NULL || lista_produtos == NULL || carrinho->itens == NULL) {
        return 0;
    }
    
    // Verifica se tem o suficiente para todos os prod.
    ItemCarrinho* item = carrinho->itens;
    while (item != NULL) {
        Produto* produto = buscar_produto_por_codigo(lista_produtos, item->codigo_produto);
        if (produto == NULL) {
            printf("Erro: Produto %d nao encontrado no sistema!\n", item->codigo_produto);
            return 0;
        }
        if (produto->quantidade < item->quantidade) {
            printf("Erro: Estoque insuficiente para %s! Disponivel: %d, Solicitado: %d\n",
                   produto->nome_prod, produto->quantidade, item->quantidade);
            return 0;
        }
        item = item->prox;
    }
    
    // atualiza base de prod
    item = carrinho->itens;
    while (item != NULL) {
        Produto* produto = buscar_produto_por_codigo(lista_produtos, item->codigo_produto);
        if (produto != NULL) {
            produto->quantidade -= item->quantidade;
        }
        item = item->prox;
    }
    
    // Gera recibo
    printf("\n--------COMPRA FINALIZADA--------\n");
    printf("Cliente: CPF %s\n", carrinho->cl_node_ptr->data->cpf);
    printf("Data: %s\n", __DATE__);
    printf("Hora: %s\n", __TIME__);
    printf("\nItens comprados:\n");
    
    ItemCarrinho* atual = carrinho->itens;
    while (atual != NULL) {
        printf("- %s: %d x R$%.2f = R$%.2f\n",
               atual->nome_produto,
               atual->quantidade,
               atual->preco_unitario,
               atual->subtotal);
        atual = atual->prox;
    }
    
    printf("\nValor total da compra: R$%.2f\n", carrinho->valor_total);
    printf("------------------------\n");
    

    limpar_carrinho(carrinho);
    
    return 1;
}

// menu compr. ------------------------------------------------------------------------

void adicionar_produto_carrinho_menu(Carrinho* carrinho, List* lista_produtos) {
    int codigo, quantidade;
    
    if (carrinho == NULL || lista_produtos == NULL) {
        printf("Erro: Sistema nao inicializado corretamente!\n");
        return;
    }
    
    printf("\n>>> ADICIONAR PRODUTO AO CARRINHO <<<\n");
    

    printf("\nProdutos disponiveis:\n");
    if (lista_produtos->head == NULL) {
        printf("Nenhum produto cadastrado no sistema!\n");
        return;
    }
    
    Produto* atual = lista_produtos->head;
    printf("CODIGO | PRODUTO                 | PRECO    | ESTOQUE\n");
    printf("-------|-------------------------|----------|--------\n");
    while (atual != NULL) {
        printf("%-6d | %-23s | R$%-6.2f | %-8d\n",
               atual->codigo_unico,
               atual->nome_prod,
               atual->preco,
               atual->quantidade);
        atual = atual->prox;
    }
    

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);
    

    Produto* produto = buscar_produto_por_codigo(lista_produtos, codigo);
    if (produto == NULL) {
        printf("Produto nao encontrado!\n");
        return;
    }
    

    printf("Digite a quantidade (estoque disponivel: %d): ", produto->quantidade);
    scanf("%d", &quantidade);
    
    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }
    
    if (quantidade > produto->quantidade) {
        printf("Quantidade solicitada maior que o estoque disponivel!\n");
        return;
    }
    

    ItemCarrinho* item = criar_item_carrinho(
        produto->codigo_unico,
        produto->nome_prod,
        produto->preco,
        quantidade
    );
    
    if (adicionar_ao_carrinho(carrinho, item)) {
        printf("Produto adicionado ao carrinho com sucesso!\n");
    } else {
        printf("Erro ao adicionar produto ao carrinho!\n");
    }
}

void remover_produto_carrinho_menu(Carrinho* carrinho) {
    int codigo;
    
    if (carrinho == NULL || carrinho->itens == NULL) {
        printf("Carrinho vazio!\n");
        return;
    }
    
    printf("\n>>> REMOVER PRODUTO DO CARRINHO <<<\n");
    

    exibir_carrinho(carrinho);
    
    printf("\nDigite o codigo do produto a ser removido: ");
    scanf("%d", &codigo);
    
    if (remover_do_carrinho(carrinho, codigo)) {
        printf("Produto removido do carrinho com sucesso!\n");
    } else {
        printf("Produto nao encontrado no carrinho!\n");
    }
}

void listar_carrinho_menu(Carrinho* carrinho) {
    if (carrinho == NULL) {
        printf("Carrinho invalido!\n");
        return;
    }
    
    exibir_carrinho(carrinho);
}

void finalizar_compra_menu(Carrinho* carrinho, List* lista_produtos) {
    char confirmacao;
    
    if (carrinho == NULL || carrinho->itens == NULL) {
        printf("Carrinho vazio! Nada para finalizar.\n");
        return;
    }
    
    printf("\n>>> FINALIZAR COMPRA <<<\n");
    

    exibir_carrinho(carrinho);
    
    printf("\nTem certeza que deseja finalizar a compra? (S/N): ");
    scanf(" %c", &confirmacao);
    
    if (confirmacao == 'S' || confirmacao == 's') {
        if (finalizar_compra(carrinho, lista_produtos)) {
            printf("Compra realizada com sucesso!\n");
        } else {
            printf("Erro ao finalizar compra!\n");
        }
    } else {
        printf("Compra cancelada.\n");
    }
}

// Menu compra
void modo_compra_acesso_menu(List* lista_produtos, Carrinho* carrinho_atual){
	clienteNode *cl_node_ptr = carrinho_atual->cl_node_ptr;
	int opcao;
	
	while (1) {
        printf("\n=== MODO COMPRA - CARRINHO do(a) %s ===\n", cl_node_ptr->data->nome);
		
		listar_carrinho_menu(carrinho_atual);
		
        printf("1. Adicionar produto ao carrinho\n");
        printf("2. Remover produto do carrinho\n");
        printf("3. Finalizar compra\n");
        printf("4. Limpar carrinho\n");
        printf("5. Voltar ao menu de busca de carrinhos\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                adicionar_produto_carrinho_menu(carrinho_atual, lista_produtos);
                break;
            case 2:
                remover_produto_carrinho_menu(carrinho_atual);
                break;
            case 3:
                finalizar_compra_menu(carrinho_atual, lista_produtos);
                break;
            case 4:
                limpar_carrinho(carrinho_atual);
                printf("Carrinho limpo!\n");
                break;
            case 5:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida :(\n");
                break;
        }
    }
}

void modo_compra_busca_menu(List* lista_produtos, ListaCarrinhos* lista_carrinhos, clienteNode *cl_head_ptr) {
    int opcao;
    Carrinho* carrinho_atual = NULL;
 
	clienteBuscaResultado *busca = malloc(sizeof(clienteBuscaResultado));
	int busca_ok = 0;
	
	char cpf[15];
	char tel[16];
	
	do {
		printf("\n-------- MODO COMPRA - CARRINHOS --------\n");
		printf("1. Buscar carrinho por CPF do cliente\n");
		printf("2. Buscar carrinho por telefone do cliente\n");
		printf("3. Listar carrinhos\n");
		printf("4. Voltar ao menu principal\n");
		scanf("%d", &opcao);
		
		//printf("%d\n",opcao);
		
		switch(opcao){
		case 1:
			if (cl_head_ptr->prox==NULL) {
				printf("Nao ha clientes cadastrados.\n");
				break;
			}
			printf("Digite o CPF do cliente (xxx.xxx.xxx-xx): ");
			getchar();
			fgets(cpf, 15, stdin);
			cpf[strcspn(cpf, "\n")] = '\0';
			
			busca_ok = buscaCliente_CPF(busca, cl_head_ptr, cpf);
			break;
			
		case 2:
			if (cl_head_ptr->prox==NULL) {
				printf("Nao ha clientes cadastrados.\n");
				break;
			}
			printf("Digite o telefone do cliente ((xx) 9xxxx-xxxx): ");
			getchar();
			fgets(tel, 16, stdin);
			tel[strcspn(tel, "\n")] = '\0';
			
			busca_ok = buscaCliente_tel(busca, cl_head_ptr, tel);
			break;
			
		case 3:
			if (cl_head_ptr->prox==NULL) {
				printf("Nao ha clientes cadastrados.\n");
				break;
			}
			if (lista_carrinhos->head==NULL) {
				printf("Nao ha carrinhos cadastrados.\n");
				break;
			}
			exibir_lista_carrinhos(lista_carrinhos);
			break;
			
		case 4:
			printf("Voltando...\n");
			return;

		default:
			printf("Opcao invalida :(\n");
			break;
        }
		
		if (opcao<3) {
			if (busca_ok == 1) {
				printf("Cliente encontrado.\n");
				
				clienteNode *cl_alvo_ptr = busca->alvo;
			
				//pegar/criar carrinho
				carrinho_atual = buscar_carrinho_por_cliente(lista_carrinhos, cl_alvo_ptr);
				if (carrinho_atual == NULL) {
					printf("O cliente nao possui um carrinho. Criando carrinho...\n");
					carrinho_atual = criar_carrinho(cl_alvo_ptr);
					
					//creio que fica aqui esse bloco
					carrinho_atual->prox = lista_carrinhos->head;
					lista_carrinhos->head = carrinho_atual;
					lista_carrinhos->size++;
					//
				} else {printf("Carrinho encontrado.\n");} 
				if (carrinho_atual == NULL) {
					printf("Erro ao criar carrinho!\n");
					return;
				}
			
				modo_compra_acesso_menu(lista_produtos, carrinho_atual);
			} else if (busca_ok == 0 && cl_head_ptr->prox!=NULL) {
				printf("Cliente nao encontrado!\n");
			} else if (busca_ok == 2) {
				if (opcao == 1) {
					printf("CPF digitado incorretamente!\n");
				} else if (opcao == 2) {
					printf("Telefone digitado incorretamente!\n");
				}
			}
		}
		
		busca_ok = 0;
	} while (opcao !=4);
}