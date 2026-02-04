#include <stdio.h>
#include <stdlib.h>
#include "compras.h"
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


Carrinho* criar_carrinho(int cpf_cliente) {
    Carrinho* novo = (Carrinho*)malloc(sizeof(Carrinho));
    if (novo == NULL) {
        printf("Erro ao criar carrinho!\n");
        return NULL;
    }
    
    novo->cpf_cliente = cpf_cliente;
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
    printf("Cliente (CPF): %d\n", carrinho->cpf_cliente);
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


Carrinho* buscar_carrinho_por_cliente(ListaCarrinhos* lista, int cpf_cliente) {
    if (lista == NULL) return NULL;
    
    Carrinho* atual = lista->head;
    while (atual != NULL) {
        if (atual->cpf_cliente == cpf_cliente) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return NULL;
}

// confirmq compra (atualizar lista base)
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
    printf("Cliente: CPF %d\n", carrinho->cpf_cliente);
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
void modo_compra_menu(List* lista_produtos, ListaCarrinhos* lista_carrinhos) {
    int opcao, cpf_cliente;
    Carrinho* carrinho_atual = NULL;
    
 
    printf("\n-------- MODO COMPRA --------\n");
    printf("Digite o CPF do cliente (apenas numeros): ");
    scanf("%d", &cpf_cliente);
    
  
    carrinho_atual = buscar_carrinho_por_cliente(lista_carrinhos, cpf_cliente);
    if (carrinho_atual == NULL) {
        carrinho_atual = criar_carrinho(cpf_cliente);
        if (carrinho_atual == NULL) {
            printf("Erro ao criar carrinho!\n");
            return;
        }
        carrinho_atual->prox = lista_carrinhos->head;
        lista_carrinhos->head = carrinho_atual;
        lista_carrinhos->size++;
    }
    
    do {
        printf("\n=== CARRINHO - CLIENTE CPF: %d ===\n", cpf_cliente);
        printf("1. Adicionar produto ao carrinho\n");
        printf("2. Remover produto do carrinho\n");
        printf("3. Listar carrinho\n");
        printf("4. Finalizar compra\n");
        printf("5. Limpar carrinho\n");
        printf("6. Voltar ao menu principal\n");
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
                listar_carrinho_menu(carrinho_atual);
                break;
            case 4:
                finalizar_compra_menu(carrinho_atual, lista_produtos);
                break;
            case 5:
                limpar_carrinho(carrinho_atual);
                printf("Carrinho limpo!\n");
                break;
            case 6:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida :(\n");
                break;
        }
        
        if (opcao != 6) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while (opcao != 6);
}