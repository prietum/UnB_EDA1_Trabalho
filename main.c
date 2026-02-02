#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"
#include "structs_produtos.h"

//funcionalidades wip (mudar aqui)
void gerenciar_clientes();  
void modo_compra();        

int main() {
    int opcao_main;
    List* lista_produtos = NULL;
    

    lista_produtos = criar_lista();
    if (lista_produtos == NULL) {
        printf("Erro ao inicializar sistema de produtos :(\n");
        return 1;
    }
    
    printf("|-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-|\n");
    printf(">------ SISTEMA DE GERENCIAMENTO DA LOJA ------<\n");
    printf("|-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-|\n");
    
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Gerenciamento de Clientes\n");
        printf("2. Gerenciamento de Produtos\n");
        printf("3. Modo Compra\n");
        printf("4. Sair do Sistema\n");
        printf("\nDigite sua opcao desejada: ");
        

        fflush(stdin);
        if (scanf("%d", &opcao_main) != 1) {
            printf("Entrada invalida... Digite um numero.\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch(opcao_main) {
            case 1:
                printf("\n--- GERENCIAMENTO DE CLIENTES ---\n");
                printf("(inserir o modulo de clientes por aqui)\n");

                break;
                
            case 2:
                printf("\n--- GERENCIAMENTO DE PRODUTOS ---\n");

                if (main_produtos(lista_produtos) == 1) {
                    printf("Saindo do sistema...\n");
                    opcao_main = 4; 
                }
                break;
                
            case 3:
                printf("\n--- MODO COMPRA ---\n");
                printf("(inserir o modulo de compras por aqui)\n");

                break;
                
            case 4:
                printf("\nEncerrando sistema...\n");
                break;
                
            default:
                printf("\nOpcao invalida... Digite um numero entre 1 e 4.\n");
                break;
        }
        
        if (opcao_main != 4) {
            printf("\nPressione Enter para voltar ao menu principal...");
            getchar();
            getchar(); 
        }
        
    } while (opcao_main != 4);
    
    printf("Limpando dados...\n");
    destruir_lista(lista_produtos);
    printf("Sistema encerrado com sucesso!\n");
    
    return 0;
}

//para abrir aplicação até agr no terminal pra debug e tudo mais
/*
gcc -c produtos.c -o produtos.o
gcc -c main.c -o main.o
gcc produtos.o main.o -o sistema_loja.exe
./sistema_loja.exe
*/