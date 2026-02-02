#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "structs_produtos.h"

// funções base p resto

//-------------------------------------------------
List* criar_lista() {
    List* lista = (List*)malloc(sizeof(List));
    if (lista == NULL) {
        printf("Erro ao alocar memoria para a lista!\n");
        return NULL;
    }
    lista->head = NULL;
    lista->size = 0;
    return lista;
}

//-------------------------------------------------
void destruir_lista(List* lista) {
    if (lista == NULL) return;
    
    Produto* atual = lista->head;
    while (atual != NULL) {
        Produto* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

//-------------------------------------------------
Produto* criar_produto(char* nome, int codigo, float preco, int quantidade) {
    Produto* novo = (Produto*)malloc(sizeof(Produto));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para o produto!\n");
        return NULL;
    }
    
    strncpy(novo->nome_prod, nome, 100);
    novo->nome_prod[100] = '\0';
    novo->codigo_unico = codigo;
    novo->preco = preco;
    novo->quantidade = quantidade;
    novo->prox = NULL;
    
    return novo;
}

//-------------------------------------------------
int lista_vazia(List* lista) {
    return (lista == NULL || lista->head == NULL);
}

//-------------------------------------------------
int cadastrar_produto(List* lista, Produto* novo_produto) {
    if (lista == NULL || novo_produto == NULL) {
        return 0;  
    }
    
    // se existe
    Produto* atual = lista->head;
    while (atual != NULL) {
        if (atual->codigo_unico == novo_produto->codigo_unico) {
            printf("Erro: Codigo %d ja existe no sistema!\n", novo_produto->codigo_unico);
            return 0;
        }
        atual = atual->prox;
    }
    
    // ir pro começo da lista
    novo_produto->prox = lista->head;
    lista->head = novo_produto;
    lista->size++;
    
    return 1; 
}

//-------------------------------------------------
void listar_produtos(List* lista) {
    if (lista_vazia(lista)) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }
    
    printf("\n>-------- LISTA DE PRODUTOS --------<\n");
    printf("Total de produtos: %d\n\n", lista->size);
    printf("Codigo  | Nome                      | Preco    | Quantidade\n");
    printf("--------|---------------------------|----------|------------\n");
    
    Produto* atual = lista->head;
    while (atual != NULL) {
        printf("%-8d| %-25s | R$%-7.2f | %-10d\n", 
               atual->codigo_unico, 
               atual->nome_prod, 
               atual->preco, 
               atual->quantidade);
        atual = atual->prox;
    }
}

//-------------------------------------------------
Produto* buscar_produto_por_codigo(List* lista, int codigo) {
    if (lista_vazia(lista)) {
        return NULL;
    }
    
    Produto* atual = lista->head;
    while (atual != NULL) {
        if (atual->codigo_unico == codigo) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return NULL;  
}

//-------------------------------------------------
Produto* buscar_produto_por_nome(List* lista, char* nome) {
    if (lista_vazia(lista) || nome == NULL) {
        return NULL;
    }
    
    Produto* atual = lista->head;
    while (atual != NULL) {
        if (strstr(atual->nome_prod, nome) != NULL) {
            return atual;  // parcial
        }
        atual = atual->prox;
    }
    
    return NULL; 
}

//-------------------------------------------------
int editar_produto(List* lista, int codigo, Produto* novos_dados) {
    if (lista_vazia(lista) || novos_dados == NULL) {
        return 0;
    }
    
    Produto* produto = buscar_produto_por_codigo(lista, codigo);
    if (produto == NULL) {
        return 0;  
    }
    
    // adiciona nova inform
    strncpy(produto->nome_prod, novos_dados->nome_prod, 100);
    produto->nome_prod[100] = '\0';
    produto->preco = novos_dados->preco;
    produto->quantidade = novos_dados->quantidade;
    
    return 1;  
}

//-------------------------------------------------
int remover_produto(List* lista, int codigo) {
    if (lista_vazia(lista)) {
        return 0;
    }
    
    Produto* atual = lista->head;
    Produto* anterior = NULL;
    
    // procura produto
    while (atual != NULL && atual->codigo_unico != codigo) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        return 0;  
    }
    
    // remover da lista
    if (anterior == NULL) {

        lista->head = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    
    free(atual);
    lista->size--;
    
    return 1;  
}

// Funções do menu

void cad_produto_menu(List* lista) {
    int qtd = 0;
    char nome[101];
    int codigo;
    float preco;
    int quantidade;
    int sucessos = 0;
    
    printf("\n>-------- CADASTRO DE PRODUTO --------<\n");
    printf("Quantos produtos serao cadastrados? ");
    scanf("%d", &qtd);
    
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Produto %d/%d ---\n", i + 1, qtd);
        
        printf("Nome do produto: ");
        getchar();  
        fgets(nome, 100, stdin);
        nome[strcspn(nome, "\n")] = '\0';  
        
        printf("Codigo unico: ");
        scanf("%d", &codigo);
        
        printf("Preco: R$ ");
        scanf("%f", &preco);
        
        printf("Quantidade em estoque: ");
        scanf("%d", &quantidade);
        
        Produto* novo = criar_produto(nome, codigo, preco, quantidade);
        if (novo != NULL) {
            if (cadastrar_produto(lista, novo)) {
                printf("Produto cadastrado com sucesso!\n");
                sucessos++;
            } else {
                free(novo); 
                printf("Falha ao cadastrar produto!\n");
            }
        }
    }
    
    printf("\nTotal de produtos cadastrados: %d/%d\n", sucessos, qtd);
}

void list_produto(List* lista) {
    listar_produtos(lista);
}

void busc_produto_menu(List* lista) {
    int opcao_bpm;
    
    do {
        printf("\n>-------- BUSCA DE PRODUTO --------<\n");
        printf("1. Buscar por nome\n");
        printf("2. Buscar por codigo\n");
        printf("3. Voltar para gerenciamento de produtos\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao_bpm);
        
        switch(opcao_bpm) {
            case 1: {
                char nome[101];
                printf("Digite o nome do produto: ");
                getchar();
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                Produto* encontrado = buscar_produto_por_nome(lista, nome);
                if (encontrado != NULL) {
                    printf("\n>-------- PRODUTO ENCONTRADO --------<\n");
                    printf("Codigo: %d\n", encontrado->codigo_unico);
                    printf("Nome: %s\n", encontrado->nome_prod);
                    printf("Preco: R$ %.2f\n", encontrado->preco);
                    printf("Quantidade: %d\n", encontrado->quantidade);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            }
                
            case 2: {
                int codigo;
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);
                
                Produto* encontrado = buscar_produto_por_codigo(lista, codigo);
                if (encontrado != NULL) {
                    printf("\n>-------- PRODUTO ENCONTRADO --------<\n");
                    printf("Codigo: %d\n", encontrado->codigo_unico);
                    printf("Nome: %s\n", encontrado->nome_prod);
                    printf("Preco: R$ %.2f\n", encontrado->preco);
                    printf("Quantidade: %d\n", encontrado->quantidade);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            }
                
            case 3:
                printf("Voltando...\n");
                return;
                
            default:
                printf("Opcao invalida :(\n");
                break;
        }
        
        if (opcao_bpm != 3) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
    } while (opcao_bpm != 3);
}

void edit_produto_menu(List* lista) {
    int codigo;
    
    printf("\n>-------- EDICAO DE PRODUTO --------<\n");
    
    if (lista_vazia(lista)) {
        printf("Nenhum produto cadastrado para editar!\n");
        return;
    }
    
    printf("Digite o codigo do produto a ser editado: ");
    scanf("%d", &codigo);
    
    Produto* produto = buscar_produto_por_codigo(lista, codigo);
    if (produto == NULL) {
        printf("Produto com codigo %d nao encontrado!\n", codigo);
        return;
    }
    

    printf("\n>-------- DADOS ATUAIS DO PRODUTO --------<\n");
    printf("Codigo: %d (nao pode ser alterado)\n", produto->codigo_unico);
    printf("1. Nome: %s\n", produto->nome_prod);
    printf("2. Preco: R$ %.2f\n", produto->preco);
    printf("3. Quantidade: %d\n", produto->quantidade);
    

    char novo_nome[101];
    float novo_preco;
    int nova_quantidade;
    
    printf("\n>-------- NOVOS DADOS --------<\n");
    printf("Novo nome: ");
    getchar();
    fgets(novo_nome, 100, stdin);
    novo_nome[strcspn(novo_nome, "\n")] = '\0';
    
    printf("Novo preco: R$ ");
    scanf("%f", &novo_preco);
    
    printf("Nova quantidade: ");
    scanf("%d", &nova_quantidade);
    
    Produto novos_dados;
    strncpy(novos_dados.nome_prod, novo_nome, 100);
    novos_dados.preco = novo_preco;
    novos_dados.quantidade = nova_quantidade;
    
    if (editar_produto(lista, codigo, &novos_dados)) {
        printf("Produto editado com sucesso :)\n");
    } else {
        printf("Erro ao editar produto :(\n");
    }
}

void remov_produto_menu(List* lista) {
    int codigo;
    char confirmacao;
    
    printf("\n>-------- REMOCAO DE PRODUTO --------<\n");
    
    if (lista_vazia(lista)) {
        printf("Nenhum produto cadastrado para remover!\n");
        return;
    }
    
    printf("Digite o codigo do produto a ser removido: ");
    scanf("%d", &codigo);
    
    Produto* produto = buscar_produto_por_codigo(lista, codigo);
    if (produto == NULL) {
        printf("Produto com codigo %d nao encontrado!\n", codigo);
        return;
    }
    
    printf("\n>-------- PRODUTO A SER REMOVIDO --------<\n");
    printf("Codigo: %d\n", produto->codigo_unico);
    printf("Nome: %s\n", produto->nome_prod);
    printf("Preco: R$ %.2f\n", produto->preco);
    printf("Quantidade: %d\n", produto->quantidade);
    
    printf("\nTem certeza que deseja remover este produto? (S/N): ");
    getchar();
    scanf("%c", &confirmacao);
    
    if (confirmacao == 'S' || confirmacao == 's') {
        if (remover_produto(lista, codigo)) {
            printf("Produto removido com sucesso!\n");
        } else {
            printf("Erro ao remover produto!\n");
        }
    } else {
        printf("Remocao cancelada.\n");
    }
}

void voltar_mainmenu() {
    printf("Voltando para menu principal...\n");
}

void main_encerra(List* lista) {
    printf("Limpando dados e saindo da aplicacao...\n");
    if (lista != NULL) {
        destruir_lista(lista);
    }
}

/*
funcao principal de gerenciamento de prod.
*/
int main_produtos(List* lista) {
    int opcao_main_prod = 0;
    
    do {
        printf("\n>-------- GERENCIAMENTO DE PRODUTOS --------<\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos cadastrados\n");
        printf("3. Buscar produto\n");
        printf("4. Editar produto\n");
        printf("5. Remover produto\n");
        printf("6. Voltar para menu principal\n");
        printf("7. Sair da aplicacao\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao_main_prod);
        
        switch(opcao_main_prod) {
            case 1:
                cad_produto_menu(lista);
                break;
            case 2:
                list_produto(lista);
                break;
            case 3:
                busc_produto_menu(lista);
                break;
            case 4:
                edit_produto_menu(lista);
                break;
            case 5:
                remov_produto_menu(lista);
                break;
            case 6:
                voltar_mainmenu();
                return 0;  // juntar isso na vers final com main
            case 7:
                main_encerra(lista);
                return 1;  // sair do terminal
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
        
        if (opcao_main_prod != 6 && opcao_main_prod != 7) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while (opcao_main_prod != 6 && opcao_main_prod != 7);
    
    return (opcao_main_prod == 7) ? 1 : 0;
}