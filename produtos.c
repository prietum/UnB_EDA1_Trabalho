#include <stdio.h>
#include "produtos.h"



void cad_produto_menu()
{
    printf("debug op 1\n");
    printf("\n>-----------------cadastro de produto-----------------<\n");

}

void list_produto()
{
    printf("debug op 2\n");

}

void busc_produto_menu()
{
    int opcao;

    printf("debug op 3\n");
    printf("\n>-----------------como realizar busca de produto-----------------<\n");
    printf("1. Nome do produto\n");
    printf("2. Codigo unico do produto\n");
    printf("3. (voltar para gerenciamento de produtos)\n");
    printf("\n Digite a opcao de sua preferencia-->");
    scanf("%d", &opcao);
    while(opcao <= 3 && opcao >= 1){
        if(opcao == 1){return;} //adicionar logica
        else if(opcao == 2){return;} //adicionar logica
        else if(opcao == 3){return main();} 
    }
 
}

void edit_produto_menu()
{
    printf("debug op 4\n");
}

void remov_produto_menu()
{
    printf("debug op 5\n");
}

void voltar_mainmenu()
{
    printf("debug op 6\n");
}

void main_encerra()
{
    printf("saindo da aplicacao...\n"); 
}


int main()
{

    int n = 0;

    while(n != 7){

    printf("\n>--------Gerenciamento de produtos--------<\n");
    printf("\n");
    printf("1. Cadastro de produto.\n"); //MM (código único, nome ,preço, quantidade);
    printf("2. Listar produtos cadastrados.\n"); // definição de produto
    printf("3. Buscar produto por codigo de identificacao.\n"); //
    printf("4. Editar dados de produto.\n");
    printf("5. Remover produto.\n");
    printf("6. (voltar para menu principal)\n");
    printf("7. (Sair da aplicacao)\n");
    printf("\n");
    printf(">--------Selecione o procedimento desejado--------<\n");
    printf("(Dica: use o numeral relacionado ao processo de sua preferencia)");
    printf("\n-->");

        scanf("%d", &n);
        if(n>=1 && n<=7){
            if(n == 1){cad_produto_menu();}
            else if(n == 2){list_produto();}
            else if(n == 3){busc_produto_menu();}
            else if(n == 4){edit_produto_menu();}
            else if(n == 5){remov_produto_menu();}
            else if(n == 6){voltar_mainmenu();} 
            else if(n == 7){main_encerra();}
        }
        else{
            printf("selecione uma opcao valida >:(\n\n");
            return main();
        }
    }
}