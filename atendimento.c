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


void inicializarCardapio() {
    // Inicializa alguns itens no cardápio
    cardapio[0] = (ItemCardapio){1, "Hambúrguer Clássico", 25.00};
    cardapio[1] = (ItemCardapio){2, "Batata Frita Grande", 12.50};
    cardapio[2] = (ItemCardapio){3, "Refrigerante Lata", 7.00};
    cardapio[3] = (ItemCardapio){4, "Milkshake Chocolate", 18.00};
    cardapio[4] = (ItemCardapio){5, "Sanduíche Natural", 20.00};
    totalItensCardapio = 5;
}

void exibirCardapio() {
    printf("\n====================================================\n");
    printf("|                 CARDAPIO LANCHONETE                |\n");
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
            printf("\n====================================================  \n");
            printf("|                 MENU PRINCIPAL                   |\n");
            printf("====================================================\n");
            printf("| 1 - Atendimento ao Cliente                       |\n");
            printf("| 2 - Vendas                                       |\n");
            printf("| 0 - Sair do Sistema                              |\n");
            printf("----------------------------------------------------\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoMenu);

            switch (opcaoMenu) {
                case 1: // Menu de Atendimento
                    opcaoAtendimento = -1; 
                    while (opcaoAtendimento != 0) {
                        printf("\n====================================================\n");
                        printf("|           ATENDIMENTO AO CLIENTE                 |\n");
                        printf("====================================================\n");
                        printf("| 1 - Pagamento de Boletos                         |\n");
                        printf("| 2 - Historico de Atendimento (Em manutencao!!)   |\n");
                        printf("| 3 - Recarga de Celular                           |\n");
                        printf("| 4 - Deposito Bancario                            |\n");
                        printf("| 5 - Saque                                        |\n");
                        printf("| 0 - Voltar ao Menu Principal                     |\n");
                        printf("----------------------------------------------------\n");
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoAtendimento);

                        switch (opcaoAtendimento) {
                            case 1:
                                exibirCardapio();
                                break;
                            case 2:
                                printf("\nOpcao 2: Historico de Atendimento\n");
                                break;
                            case 3:
                                printf("\nOpcao 3: Recarga de Celular\n");
                                break;
                            case 4:
                                printf("\nOpcao 4: Deposito Bancario\n");
                                break;
                            case 5:
                                printf("\nOpcao 5: Saque\n");
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
                        printf("|                     VENDAS                       |\n");
                        printf("====================================================\n");
                        printf("| 1 - Registrar Venda de Aposta                    |\n");
                        printf("| 2 - Consulta de Resultados (Em manutencao!!)     |\n");
                        printf("| 3 - Pagamento de Premios                         |\n");
                        printf("| 0 - Voltar ao Menu Principal                     |\n");
                        printf("----------------------------------------------------\n");
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoVendas);

                        switch (opcaoVendas) {
                            case 1:
                                printf("\nOpcao 1: Registrar Venda de Aposta\n");
                                break;
                            case 2:
                                printf("\nOpcao 2: Consulta de Resultados\n");
                                break;
                            case 3:
                                printf("\nOpcao 3: Pagamento de Premios\n");
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