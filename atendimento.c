#include <stdio.h>    // Para printf, scanf
#include <string.h>   // Necessário para usar strcmp

// Definição de constantes
#define SENHA_AD 1234
#define LOGIN_AD "admin" // Constantes de string precisam de aspas

typedef struct {
    int id;
    char nome[50];
    float preco;
} ItemCardapio;

ItemCardapio cardapio[10];
int totalItensCardapio = 0;

void limparTela(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

/*
Vai Salgadão (Pastel de carne com queijo derretendo)



*/



void inicializarCardapio() {
    //  Salgados Fritos
    cardapio[0] = (ItemCardapio){1, "Pastel de Carne (Massa crocante com carne moída temperada)", 8.50};
    cardapio[1] = (ItemCardapio){2, "Pastel de Queijo (Queijo derretido na massa frita)", 7.50};
    cardapio[2] = (ItemCardapio){3, "Coxinha (Massa de batata com frango desfiado)", 6.00};
    cardapio[3] = (ItemCardapio){4, "Kibe (Trigo, carne moída e hortelã)", 5.50};
    cardapio[4] = (ItemCardapio){5, "Bolinha de Queijo (Massa crocante com queijo cremoso)", 6.50};
    cardapio[5] = (ItemCardapio){6, "Risole de Presunto e Queijo", 5.00};
    cardapio[6] = (ItemCardapio){7, "Enroladinho de Salsicha", 4.50};

    //  Sanduíches
    cardapio[7] = (ItemCardapio){8, "Misto Quente (Pão de forma com queijo e presunto gratinado)", 10.00};
    cardapio[8] = (ItemCardapio){9, "Sanduíche Natural (Pão integral com frango, cenoura e requeijão)", 12.00};
    cardapio[9] = (ItemCardapio){10, "Bauru (Pão francês com rosbife, queijo derretido e tomate)", 15.00};
    cardapio[10] = (ItemCardapio){11, "Cachorro-Quente (Pão com salsicha, purê, batata palha e molhos)", 14.00};

    //  Salgados Assados
    cardapio[11] = (ItemCardapio){12, "Empada de Frango (Massa folhada com frango e catupiry)", 7.00};
    cardapio[12] = (ItemCardapio){13, "Esfiha de Carne (Massa aberta com carne moída temperada)", 5.00};
    cardapio[13] = (ItemCardapio){14, "Pão de Queijo (Tradicional mineiro, quentinho)", 4.00};
    cardapio[14] = (ItemCardapio){15, "Torta de Frango (Massa crocante com recheio cremoso)", 9.00};

    //  Porções
    cardapio[15] = (ItemCardapio){16, "Batata Frita (Porção crocante com sal)", 18.00};
    cardapio[16] = (ItemCardapio){17, "Batata Frita com Cheddar e Bacon", 25.00};
    cardapio[17] = (ItemCardapio){18, "Mandioquinha Frita", 20.00};
    cardapio[18] = (ItemCardapio){19, "Isca de Frango (400g com molho barbecue)", 28.00};

    totalItensCardapio = 19;
}


void exibirCardapio() {
    printf("\n====================================================\n");
    printf("|       CARDAPIO LANCHONETE WESLEY SALGADAO        |\n");
    printf("====================================================\n");
    printf("| ID | NOME DO ITEM                 | PRECO (R$)   |\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < totalItensCardapio; i++) {
        printf("| %-2d | %-28s | %-12.2f |\n", cardapio[i].id, cardapio[i].nome, cardapio[i].preco);
    }
    printf("====================================================\n");
}





int main() {
    inicializarCardapio();
    // Variaveis Locais
    char login[20];
    int senha;

    int opcaoMenu = -1;
    int opcaoAtendimento = -1;
    int opcaoVendas = -1;

    // Tela de Login
    printf("====================================================\n");
    printf("|                    LANCHONETE                    |\n");
    printf("|                 WESLEY SALGADAO                  |\n");
    printf("====================================================\n");
    printf("\nLogin de acesso: ");+
    scanf("%s", login);
    printf("Senha: ");
    scanf("%d", &senha);

    // Validador de acesso
    if (strcmp(login, LOGIN_AD) == 0 && senha == SENHA_AD) {
        printf("\nAcesso permitido!\n");

        // Loop do Menu Principal
        while (opcaoMenu != 0) {
             printf("\n====================================================\n");
            printf("|                   MENU PRINCIPAL                 |\n");
            printf("====================================================\n");
            printf("| 1 - Fazer Pedido (Atendimento ao Cliente)        |\n");
            printf("| 2 - Gerenciar Vendas                             |\n");
            printf("| 0 - Sair do Sistema                              |\n");
            printf("----------------------------------------------------\n");
            scanf("%d", &opcaoMenu);

            switch (opcaoMenu) {
                case 1: // Menu de Atendimento
                    opcaoAtendimento = -1; 
                    while (opcaoAtendimento != 0) {
                        limparTela();
                        printf("\n====================================================\n");
                        printf("|              FAZER PEDIDO                          |\n");
                        printf("====================================================\n");
                        printf("| 1 - Registrar Novo Pedido                        |\n");
                        printf("| 2 - Exibir Cardápio                              |\n");
                        printf("| 0 - Voltar ao Menu Principal                     |\n");
                        printf("----------------------------------------------------\n");
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoAtendimento);

                        switch (opcaoAtendimento) {
                            case 1:
                                printf("\nVoltando ao Menu Principal...\n");
                                break;
                            case 2:
                                limparTela();
                                exibirCardapio();
                                break;
                            case 0:
                                printf("\nVoltando ao Menu Principal...\n");
                                break;
                            default:
                                printf("\nOpcao invalida. Tente novamente.\n");
                                break;
                        }
                    }
                    break;
                case 2: // Menu de Vendas
                    opcaoVendas = -1;
                    while (opcaoVendas != 0) {
                        printf("\n====================================================\n");
                        printf("|                  GERENCIAR VENDAS                |\n");
                        printf("====================================================\n");
                        printf("| 1 - Visualizar Todas as Vendas                   |\n");
                        printf("| 0 - Voltar ao Menu Principal                     |\n");
                        printf("----------------------------------------------------\n");
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoVendas);

                        switch (opcaoVendas) {
                            case 1:
                                printf("\nOpcao 1: Registrar Venda de Aposta\n");
                                break;
                            case 0:
                                printf("\nVoltando ao Menu Principal...\n");
                                break;
                            default:
                                printf("\nOpcao invalida. Tente novamente.\n");
                                break;
                        }
                    }
                    break;
                case 0: // Sair do Sistema
                    printf("\nSaindo do Sistema...\n");
                    break;
                default:
                    printf("\nOpcao invalida. Tente novamente.\n");
                    break;
            }
        }
        printf("\n");
        printf("====================================================\n");
        printf("|         SESSAO FINALIZADA COM SUCESSO            |\n");
        printf("|        Obrigado por utilizar o sistema!!         |\n");
        printf("====================================================\n");

    } else {
        printf("\nACESSO NEGADO - Credenciais invalidas.\n");
        printf("Por favor, contate o administrador.\n");
    }

    return 0;
}