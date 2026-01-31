#include <stdio.h>



int cad_produto()
{
    printf("debug op 1\n");

    return 0;
}

int list_produto()
{
    printf("debug op 2\n");

    return 0;
}

int busc_produto()
{
    printf("debug op 3\n");

    return 0;
}

int edit_produto()
{
    printf("debug op 4\n");

    return 0;
}

int remov_produto()
{
    printf("debug op 5\n");

    return 0;
}

int voltar_mainmenu()
{
    printf("debug op 6\n");

    return 0;
}


int main()
{

    int n;

    printf(">--------Gerenciamento de produtos--------<\n");
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
    printf("(Dica: use o numeral relacionado ao processo de sua preferencia)\n");

    scanf("%d", &n);
        if(n>=1 && n<=7){
            if(n == 1){cad_produto();}
            else if(n == 2){list_produto();}
            else if(n == 3){busc_produto();}
            else if(n == 4){edit_produto();}
            else if(n == 5){remov_produto();}
            else if(n == 6){voltar_mainmenu();} 
            else if(n == 7){printf("saindo da aplicacao...\n"); return 0;}
        }
        else
            printf("selecione uma opcao valida >:(\n");
            return main();

    
    return 0;

}