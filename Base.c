#include <stdio.h>    // Para printf, scanf
#include <string.h>   // Necessário para usar strcmp
#include <stdlib.h>   // Para usar system("cls") ou system("clear")

// Definição de constantes
#define SENHA_ADMIN 1234
#define LOGIN_ADMIN "admin"

// Estrutura para os itens do cardápio
typedef struct {
    int id;
    char nome[50];
    float preco;
} ItemCardapio;

// Estrutura para registrar uma venda
typedef struct {
    int idVenda;
    int idItemVendido;
    char nomeItem[50];
    int quantidade;
    float precoUnitario;
    float totalVenda;
} RegistroVenda;

// Variáveis globais para cardápio e vendas (para simplificar neste exemplo)
ItemCardapio cardapio[10];
int totalItensCardapio = 0;

RegistroVenda vendas[100];
int totalVendas = 0;
int proximoIdVenda = 1;

// --- Funções Auxiliares ---

void limparTela() {
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para Linux/macOS
#endif
}

void inicializarCardapio() {
    // Inicializa alguns itens no cardápio
    cardapio[0] = (ItemCardapio){1, "Hambúrguer Clássico", 25.00};
    cardapio[1] = (ItemCardapio){2, "Hamburguer duplo", 30.00};
    cardapio[2] = (ItemCardapio){3, "Hamburguer triplo", 35.00};
    cardapio[3] = (ItemCardapio){4, "Batata Frita Grande", 12.50};
    cardapio[4] = (ItemCardapio){5, "Refrigerante Lata", 7.00};
    cardapio[5] = (ItemCardapio){6, "Milkshake Chocolate", 18.00};
    cardapio[6] = (ItemCardapio){7, "Sanduíche Natural", 20.00};
    


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

void registrarVenda() {
    int idItem, quantidade;
    float totalItem;
    char continuar = 's';

    printf("\n--- REGISTRAR NOVA VENDA ---\n");

    if (totalItensCardapio == 0) {
        printf("Cardápio vazio! Não é possível registrar vendas.\n");
        return;
    }

    // Loop para adicionar múltiplos itens à mesma venda
    while (continuar == 's' || continuar == 'S') {
        exibirCardapio();
        printf("Digite o ID do item para vender (0 para cancelar): ");
        scanf("%d", &idItem);

        if (idItem == 0) {
            printf("Venda cancelada.\n");
            return;
        }

        int itemEncontrado = 0;
        for (int i = 0; i < totalItensCardapio; i++) {
            if (cardapio[i].id == idItem) {
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                if (quantidade <= 0) {
                    printf("Quantidade inválida. Operação cancelada.\n");
                    return;
                }

                totalItem = cardapio[i].preco * quantidade;

                // Armazena a venda
                if (totalVendas < 100) { // Limite de 100 vendas para este exemplo
                    vendas[totalVendas].idVenda = proximoIdVenda;
                    vendas[totalVendas].idItemVendido = cardapio[i].id;
                    strcpy(vendas[totalVendas].nomeItem, cardapio[i].nome);
                    vendas[totalVendas].quantidade = quantidade;
                    vendas[totalVendas].precoUnitario = cardapio[i].preco;
                    vendas[totalVendas].totalVenda = totalItem;
                    totalVendas++;
                    printf("Item '%s' (x%d) adicionado à venda. Total do item: R$ %.2f\n", cardapio[i].nome, quantidade, totalItem);
                } else {
                    printf("Limite de vendas atingido. Não é possível registrar mais vendas.\n");
                }
                itemEncontrado = 1;
                break;
            }
        }

        if (!itemEncontrado) {
            printf("ID de item inválido. Tente novamente.\n");
        }

        printf("Adicionar outro item à venda? (S/N): ");
        scanf(" %c", &continuar); // Espaço antes de %c para consumir o newline
    }
    proximoIdVenda++; // Incrementa o ID da venda após a conclusão de uma "sessão" de venda
    printf("\nVenda registrada com sucesso!\n");
}

void visualizarVendas() {
    printf("\n====================================================\n");
    printf("|                REGISTRO DE VENDAS                  |\n");
    printf("====================================================\n");
    if (totalVendas == 0) {
        printf("|              Nenhuma venda registrada ainda.       |\n");
    } else {
        printf("| ID Venda | ITEM                      | QTD | PRECO UN. | TOTAL (R$) |\n");
        printf("----------------------------------------------------------------------\n");
        float totalGeralVendas = 0;
        for (int i = 0; i < totalVendas; i++) {
            printf("| %-8d | %-25s | %-3d | %-9.2f | %-10.2f |\n",
                   vendas[i].idVenda, vendas[i].nomeItem, vendas[i].quantidade,
                   vendas[i].precoUnitario, vendas[i].totalVenda);
            totalGeralVendas += vendas[i].totalVenda;
        }
        printf("----------------------------------------------------------------------\n");
        printf("|                                        TOTAL GERAL DE VENDAS: R$ %.2f |\n", totalGeralVendas);
    }
    printf("====================================================\n");
}

int main() {
    char login[20];
    int senha;

    int opcaoMenu = -1;
    int opcaoAtendimento = -1; // Usado para "Fazer Pedido"
    int opcaoVendas = -1;     // Usado para "Gerenciar Vendas"

    inicializarCardapio(); // Carrega os itens iniciais do cardápio

    // Tela de Login
    limparTela();
    printf("====================================================\n");
    printf("|              LANCHONETE MEU                       |\n");
    printf("|              GRELHADO FAVORITO                    |\n");
    printf("====================================================\n");
    printf("\nLogin de acesso: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%d", &senha);

    // Validador de acesso
    if (strcmp(login, LOGIN_ADMIN) == 0 && senha == SENHA_ADMIN) {
        printf("\nAcesso permitido!\n");

        // Loop do Menu Principal
        while (opcaoMenu != 0) {
            limparTela();
            printf("\n====================================================\n");
            printf("|                   MENU PRINCIPAL                 |\n");
            printf("====================================================\n");
            printf("| 1 - Fazer Pedido (Atendimento ao Cliente)        |\n");
            printf("| 2 - Gerenciar Vendas                             |\n");
            printf("| 0 - Sair do Sistema                              |\n");
            printf("----------------------------------------------------\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoMenu);

            switch (opcaoMenu) {
                case 1: // Fazer Pedido
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
                                registrarVenda();
                                printf("\nPressione ENTER para continuar...");
                                getchar(); // Consumir o newline pendente
                                getchar(); // Esperar pelo ENTER
                                break;
                            case 2:
                                exibirCardapio();
                                printf("\nPressione ENTER para continuar...");
                                getchar(); // Consumir o newline pendente
                                getchar(); // Esperar pelo ENTER
                                break;
                            case 0:
                                printf("\nVoltando ao Menu Principal...\n");
                                break;
                            default:
                                printf("\nOpcao invalida. Tente novamente.\n");
                                printf("\nPressione ENTER para continuar...");
                                getchar(); // Consumir o newline pendente
                                getchar(); // Esperar pelo ENTER
                                break;
                        }
                    }
                    break;
                case 2: // Gerenciar Vendas
                    opcaoVendas = -1;
                    while (opcaoVendas != 0) {
                        limparTela();
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
                                visualizarVendas();
                                printf("\nPressione ENTER para continuar...");
                                getchar(); // Consumir o newline pendente
                                getchar(); // Esperar pelo ENTER
                                break;
                            case 0:
                                printf("\nVoltando ao Menu Principal...\n");
                                break;
                            default:
                                printf("\nOpcao invalida. Tente novamente.\n");
                                printf("\nPressione ENTER para continuar...");
                                getchar(); // Consumir o newline pendente
                                getchar(); // Esperar pelo ENTER
                                break;
                        }
                    }
                    break;
                case 0: // Sair do Sistema
                    printf("\nSaindo do Sistema...\n");
                    break;
                default:
                    printf("\nOpcao invalida. Tente novamente.\n");
                    printf("\nPressione ENTER para continuar...");
                    getchar(); // Consumir o newline pendente
                    getchar(); // Esperar pelo ENTER 
                    break;
            }
        }
        printf("\n");
        printf("====================================================\n");
        printf("|          SESSAO FINALIZADA COM SUCESSO           |\n");
        printf("|       Obrigado por utilizar o sistema!!          |\n");
        printf("====================================================\n");

    } else {
        printf("\nACESSO NEGADO - Credenciais invalidas.\n");
        printf("Por favor, contate o administrador.\n");
    }

    return 0;
}