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


void inicializarCardapio() {
    cardapio[0] = (ItemCardapio){1, "X-Safadao (Carne, queijo, bacon, molho              )", 25.00};
    cardapio[1] = (ItemCardapio){2, "X-Laricao (Carne, queijo, alface, tomate            )", 12.50};
    cardapio[2] = (ItemCardapio){3, "X-Treme Treme (Carne, queijo, barbecue              )", 7.00};
    cardapio[3] = (ItemCardapio){4, "Pastel do Véi Preguiça (Massa, carne, queijo        )", 18.00};
    cardapio[4] = (ItemCardapio){5, "Empadão do Soneca (Massa, frango, requeijão         )", 20.00};

    cardapio[5] = (ItemCardapio){6, "X-Bomba Atomica (Duplo, queijo, bacon, alface       )", 30.00};
    cardapio[6] = (ItemCardapio){7, "X-Termonuke (Picante, cheddar, cebola, picles       )", 28.00};
    cardapio[7] = (ItemCardapio){8, "X-Ditador (Premium, queijo, bacon, cebola, maionese )", 27.50};
    cardapio[8] = (ItemCardapio){9, "X-Revolucao (Vegano, queijo, rúcula, tomate, molho  )", 26.00};

    cardapio[9] = (ItemCardapio){10, "Bomba de Chocolate (Brownie, ganache, chocolate    )", 15.00};
    cardapio[10] = (ItemCardapio){11, "Torta Termonuclear (Chocolate, doce de leite,     )", 18.00};
    cardapio[11] = (ItemCardapio){12, "Tortadela (Massa, brigadeiro, beijinho, granulados)", 17.00};

    totalItensCardapio = 12;
}




void exibirCardapio() {
    printf("\n====================================================\n");
    printf("|         CARDAPIO LANCHONETE KIM LANCHUN          |\n");
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
    printf("|                 LANCHONETE MEU                   |\n");
    printf("|               GRELHADO FAVORITO                  |\n");
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