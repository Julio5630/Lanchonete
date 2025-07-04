#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

// Definição de constantes
#define SENHA_AD 1234
#define LOGIN_AD "admin" 

// Número máximo de itens no cardápio e de registros de vendas
#define MAX_ITENS_CARDAPIO 50 
#define MAX_VENDAS 500       
#define MAX_ITENS_PEDIDO 20   

// Estrutura para um item do cardápio
typedef struct {
    int id;
    char nome[100]; 
    float preco;
} ItemCardapio;

// Estrutura para um registro de venda (usada para histórico do admin)
typedef struct {
    int idVenda;
    int idItemVendido;
    char nomeItem[100]; 
    int quantidade;
    float precoUnitario;
    float totalVenda;
} RegistroVenda;

// estrutura para os itens do pedido atual (para o comprovante)
typedef struct {
    int idItem;
    char nomeItem[100];
    int quantidade;
    float precoUnitario;
    float subtotalItem;
} ItemPedidoAtual;

// Arrays e contadores globais
ItemCardapio cardapio[MAX_ITENS_CARDAPIO];
int totalItensCardapio = 0;

RegistroVenda vendas[MAX_VENDAS];
int totalVendas = 0;
int proximoIdVenda = 1; // Será ajustado ao carregar dados do CSV

// --- PROTÓTIPOS DE FUNÇÕES ---
// (Essas linhas informam ao compilador sobre as funções que serão definidas depois)
void limparTela();
void limparBufferEntrada();
void salvarVendasCSV(const char *nomeArquivo);
void carregarVendasCSV(const char *nomeArquivo);
void inicializarCardapio();
void exibirCardapio();
void gerarComprovante(ItemPedidoAtual pedidoAtual[], int numItensPedido, float subtotal, float desconto, float totalFinal);
void registrarVendaComDesconto();
void visualizarVendas();

// --- DEFINIÇÕES DAS FUNÇÕES ---

// Função para limpar a tela do console
void limparTela() {
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para Linux/macOS
#endif
}

// Função para consumir o restante da linha do buffer de entrada (incluindo o '\n')
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para salvar os dados de vendas em um arquivo CSV
void salvarVendasCSV(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w"); // "w" para escrever (cria ou sobrescreve o arquivo)
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", nomeArquivo);
        printf("Pressione ENTER para continuar...");
        limparBufferEntrada();
        return;
    }

    // Escreve o cabeçalho do CSV
    fprintf(arquivo, "ID Venda;ID Item;Nome Item;Quantidade;Preco Unitario;Total Item\n");

    // Escreve os dados de cada venda
    for (int i = 0; i < totalVendas; i++) {
        fprintf(arquivo, "%d;%d;%s;%d;%.2f;%.2f\n",
                vendas[i].idVenda,
                vendas[i].idItemVendido,
                vendas[i].nomeItem,
                vendas[i].quantidade,
                vendas[i].precoUnitario,
                vendas[i].totalVenda);
    }

    fclose(arquivo);
    // Removida a mensagem de "salvo com sucesso" para chamadas automáticas,
    // para não poluir a saída quando o salvamento é implícito.
    // printf("\nHistorico de vendas salvo com sucesso em '%s'.\n", nomeArquivo);
    // printf("Pressione ENTER para continuar...");
    // limparBufferEntrada(); // Não é necessário pausar para salvamento automático
}

// Função para carregar os dados de vendas de um arquivo CSV
void carregarVendasCSV(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); // "r" para leitura
    if (arquivo == NULL) {
        printf("Arquivo '%s' nao encontrado ou erro ao abrir. Iniciando com historico vazio.\n", nomeArquivo);
        return;
    }

    // Pula o cabeçalho
    char linha[256]; // Buffer para ler a linha
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        // Arquivo vazio ou erro ao ler cabeçalho
        fclose(arquivo);
        return;
    }

    totalVendas = 0;
    int maxIdVenda = 0; // Para encontrar o maior ID de venda e atualizar proximoIdVenda

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (totalVendas >= MAX_VENDAS) {
            printf("Limite de vendas atingido (%d). Nao foi possivel carregar todas as vendas do arquivo.\n", MAX_VENDAS);
            break;
        }

        if (sscanf(linha, "%d;%d;%99[^;];%d;%f;%f",
                   &vendas[totalVendas].idVenda,
                   &vendas[totalVendas].idItemVendido,
                   vendas[totalVendas].nomeItem, 
                   &vendas[totalVendas].quantidade,
                   &vendas[totalVendas].precoUnitario,
                   &vendas[totalVendas].totalVenda) == 6) { 
            
            vendas[totalVendas].nomeItem[strcspn(vendas[totalVendas].nomeItem, "\n\r")] = '\0';

            if (vendas[totalVendas].idVenda > maxIdVenda) {
                maxIdVenda = vendas[totalVendas].idVenda;
            }
            totalVendas++;
        } else {
            printf("Erro ao ler linha do arquivo CSV: %s", linha);
        }
    }

    fclose(arquivo);
    proximoIdVenda = maxIdVenda + 1; 
    printf("Historico de vendas carregado com sucesso de '%s'. Total de %d vendas.\n", nomeArquivo, totalVendas);
}

// Inicializa o cardápio com itens predefinidos
void inicializarCardapio() {
    // Salgados Fritos
    cardapio[totalItensCardapio++] = (ItemCardapio){1, "Pastel de Carne (Massa crocante com carne moída temperada)", 8.50};
    cardapio[totalItensCardapio++] = (ItemCardapio){2, "Pastel de Queijo (Queijo derretido na massa frita)", 7.50};
    cardapio[totalItensCardapio++] = (ItemCardapio){3, "Coxinha (Massa de batata com frango desfiado)", 6.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){4, "Kibe (Trigo, carne moída e hortelã)", 5.50};
    cardapio[totalItensCardapio++] = (ItemCardapio){5, "Bolinha de Queijo (Massa crocante com queijo cremoso)", 6.50};
    cardapio[totalItensCardapio++] = (ItemCardapio){6, "Risole de Presunto e Queijo", 5.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){7, "Enroladinho de Salsicha", 4.50};
    // Porções
    cardapio[totalItensCardapio++] = (ItemCardapio){8, "Batata Frita (Porção crocante com sal)", 18.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){9, "Batata Frita com Cheddar e Bacon", 25.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){10, "Mandioquinha Frita", 20.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){11, "Isca de Frango (400g com molho barbecue)", 28.00};

    // Bebidas
    cardapio[totalItensCardapio++] = (ItemCardapio){12, "Coca Cola", 7.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){13, "Refrigerante Lata - Guaraná Antarctica", 7.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){14, "Refrigerante Lata - Fanta Laranja", 7.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){15, "Suco Natural Laranja (300ml)", 9.00};
    cardapio[totalItensCardapio++] = (ItemCardapio){16, "Cantina da Serra (galao 5L)", 4.00}; 
    cardapio[totalItensCardapio++] = (ItemCardapio){17, "Água Mineral (sem gás)", 3.50};
}

// Exibe o cardápio
void exibirCardapio() {
    printf("\n========================================================================================\n");
    printf("|                              CARDAPIO LANCHONETE WESLEY SALGADAO                       |\n"); 
    printf("========================================================================================\n");
    printf("| ID | NOME DO ITEM                                                               | PRECO (R$) |\n"); 
    printf("----------------------------------------------------------------------------------------\n"); 
    for (int i = 0; i < totalItensCardapio; i++) {
        printf("| %-2d | %-60s | %-10.2f |\n", cardapio[i].id, cardapio[i].nome, cardapio[i].preco);
    }
    printf("========================================================================================\n"); 
    printf("\nPressione ENTER para continuar...");
    limparBufferEntrada();
}

// Gera e exibe o comprovante do pedido
void gerarComprovante(ItemPedidoAtual pedidoAtual[], int numItensPedido, float subtotal, float desconto, float totalFinal) {
    limparTela();
    
    printf("\n=====================================================================================================\n");
    printf("|                                        COMPROVANTE DE PEDIDO                                      |\n"); 
    printf("=====================================================================================================\n");
    printf("ID do Pedido: %d\n", proximoIdVenda - 1); // Exibe o ID da venda que acabou de ser processada
    printf("-----------------------------------------------------------------------------------------------------\n"); 
    printf("| Qtd | Item                                                                 | Preco Unit. | Subtotal |\n"); 
    printf("-----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < numItensPedido; i++) {
        printf("| %-3d | %-60s | %-12.2f| %-9.2f|\n",
               pedidoAtual[i].quantidade,
               pedidoAtual[i].nomeItem,
               pedidoAtual[i].precoUnitario,
               pedidoAtual[i].subtotalItem);
    }

    printf("-----------------------------------------------------------------------------------------------------\n"); 
    printf("Subtotal: R$ %.2f\n", subtotal);
    if (desconto > 0) {
        printf("Desconto aplicado: R$ %.2f\n", desconto);
    }
    printf("Total a Pagar: R$ %.2f\n", totalFinal);
    printf("=====================================================================================================\n");
    printf("|                                  Obrigado pela preferencia!                                      |\n"); 
    printf("=====================================================================================================\n");
    printf("\nPressione ENTER para continuar...");
    limparBufferEntrada(); 
}

// Registra uma nova venda no histórico e aplica o desconto se aplicável
void registrarVendaComDesconto() {
    int idItem, quantidade;
    float subtotalPedido = 0.0;
    float totalFinal = 0.0;
    float valorDesconto = 0.0;
    char continuar = 's';
    const float DESCONTO_PERCENTUAL = 0.05; // 5% de desconto
    const float VALOR_MINIMO_DESCONTO = 50.00;

    // Array temporário para armazenar os itens do pedido atual para o comprovante
    ItemPedidoAtual pedidoAtual[MAX_ITENS_PEDIDO];
    int numItensPedido = 0; // Contador de itens neste pedido específico

    printf("\n--- REGISTRAR NOVO PEDIDO ---\n");

    if (totalItensCardapio == 0) {
        printf("Cardápio vazio! Não é possível registrar vendas.\n");
        printf("\nPressione ENTER para continuar...");
        limparBufferEntrada();
        return;
    }

    // Loop para adicionar múltiplos itens à mesma venda
    while (continuar == 's' || continuar == 'S') {
        limparTela();
        exibirCardapio(); // Exibe o cardápio a cada adição de item
        printf("\nSubtotal atual do pedido: R$ %.2f\n", subtotalPedido);
        printf("Digite o ID do item para vender (0 para finalizar o pedido): ");
        if (scanf("%d", &idItem) != 1) { 
            printf("Entrada inválida. Tente novamente.\n");
            limparBufferEntrada();
            continue; 
        }
        limparBufferEntrada();

        if (idItem == 0) {
            break; 
        }

        int itemEncontrado = 0;
        for (int i = 0; i < totalItensCardapio; i++) {
            if (cardapio[i].id == idItem) {
                printf("Digite a quantidade: ");
                if (scanf("%d", &quantidade) != 1) { 
                    printf("Entrada inválida. Tente novamente.\n");
                    limparBufferEntrada();
                    itemEncontrado = 2; // Sinaliza erro de quantidade
                    break;
                }
                limparBufferEntrada();

                if (quantidade <= 0) {
                    printf("Quantidade inválida. Operação cancelada.\n");
                    itemEncontrado = 2; 
                    break;
                }

                float subtotalDoItem = cardapio[i].preco * quantidade;

                // Armazena o item no array do pedido atual para o comprovante
                if (numItensPedido < MAX_ITENS_PEDIDO) {
                    pedidoAtual[numItensPedido].idItem = cardapio[i].id;
                    strcpy(pedidoAtual[numItensPedido].nomeItem, cardapio[i].nome);
                    pedidoAtual[numItensPedido].quantidade = quantidade;
                    pedidoAtual[numItensPedido].precoUnitario = cardapio[i].preco;
                    pedidoAtual[numItensPedido].subtotalItem = subtotalDoItem;
                    numItensPedido++;
                    subtotalPedido += subtotalDoItem; 
                    printf("Item '%s' (x%d) adicionado ao pedido. Subtotal do item: R$ %.2f\n", cardapio[i].nome, quantidade, subtotalDoItem);
                } else {
                    printf("Limite de itens para este pedido atingido (%d itens). Este item não será adicionado ao comprovante.\n", MAX_ITENS_PEDIDO);
                }

                // Armazena a venda também no histórico global (para o admin)
                if (totalVendas < MAX_VENDAS) {
                    vendas[totalVendas].idVenda = proximoIdVenda; 
                    vendas[totalVendas].idItemVendido = cardapio[i].id;
                    strcpy(vendas[totalVendas].nomeItem, cardapio[i].nome);
                    vendas[totalVendas].quantidade = quantidade;
                    vendas[totalVendas].precoUnitario = cardapio[i].preco;
                    vendas[totalVendas].totalVenda = subtotalDoItem;
                    totalVendas++;
                } else {
                    printf("Aviso: Limite de vendas no histórico atingido. Este item não será registrado no histórico geral.\n");
                }
                itemEncontrado = 1;
                break;
            }
        }

        if (!itemEncontrado) {
            printf("ID de item inválido. Tente novamente.\n");
        } else if (itemEncontrado == 1) { // Apenas pergunta para continuar se um item foi adicionado com sucesso
            printf("Adicionar outro item ao pedido? (S/N): ");
            scanf(" %c", &continuar); 
            limparBufferEntrada(); 
        }
    }

    // Calcula o total e aplica o desconto
    totalFinal = subtotalPedido;
    if (subtotalPedido > VALOR_MINIMO_DESCONTO) {
        valorDesconto = subtotalPedido * DESCONTO_PERCENTUAL;
        totalFinal = subtotalPedido - valorDesconto;
    }

    printf("\n--- RESUMO DO PEDIDO ---\n");
    printf("Subtotal do pedido: R$ %.2f\n", subtotalPedido);
    if (valorDesconto > 0) {
        printf("Desconto aplicado (5%%): -R$ %.2f\n", valorDesconto);
    } else {
        printf("Nenhum desconto aplicado. Compre mais de R$%.2f para ganhar 5%% de desconto!\n", VALOR_MINIMO_DESCONTO);
    }
    printf("Total a pagar: R$ %.2f\n", totalFinal);
    printf("\nPedido finalizado com sucesso!\n");

    // Gera o comprovante 
    if (numItensPedido > 0) {
        gerarComprovante(pedidoAtual, numItensPedido, subtotalPedido, valorDesconto, totalFinal);
        // --- CHAMO A FUNÇÃO DE SALVAR AQUI, APÓS FINALIZAR O PEDIDO ---
        salvarVendasCSV("historico_vendas.csv"); 
    } else {
        printf("Nenhum item foi adicionado ao pedido.\n");
        printf("\nPressione ENTER para continuar...");
        limparBufferEntrada();
    }

    proximoIdVenda++; 
}

// Exibe todas as vendas registradas (para a área de gerenciamento)
void visualizarVendas() {
    printf("\n============================================================================================================================\n");
    printf("|                                                  HISTORICO DE VENDAS                                                     |\n"); 
    printf("============================================================================================================================\n");

    if (totalVendas == 0) {
        printf("\nNenhuma venda registrada ainda.\n");
        printf("============================================================================================================================\n"); 
        printf("\nPressione ENTER para continuar...");
        limparBufferEntrada();
        return;
    }

    printf("| ID Venda | ID Item | Item                                                         | Qtd | Preco Unit. | Total Item |\n"); 
    printf("----------------------------------------------------------------------------------------------------------------------------\n"); 
    float totalGeralVendas = 0.0;
    for (int i = 0; i < totalVendas; i++) {
        printf("| %-9d| %-8d| %-60s | %-4d| %-12.2f| %-11.2f|\n",
               vendas[i].idVenda,
               vendas[i].idItemVendido,
               vendas[i].nomeItem,
               vendas[i].quantidade,
               vendas[i].precoUnitario,
               vendas[i].totalVenda);
        totalGeralVendas += vendas[i].totalVenda;
    }
    printf("----------------------------------------------------------------------------------------------------------------------------\n"); 

    // Calculando os espaços para alinhar o total à direita
    char totalStr[50]; 
    sprintf(totalStr, "R$ %.2f", totalGeralVendas);
    int lenTotalStr = strlen(totalStr);
    int fixedTextLen = strlen("| TOTAL GERAL: "); 
    int totalLineLen = 108; // Largura interna da tabela (ajustar se mudar as colunas)
    int padding = totalLineLen - fixedTextLen - lenTotalStr;

    printf("| TOTAL GERAL: %*s%s |\n", padding, "", totalStr); 

    printf("============================================================================================================================\n"); 

    printf("\nPressione ENTER para continuar...");
    limparBufferEntrada(); 
}

// Função principal
int main() {
    inicializarCardapio();
    // --- CARREGA AS VENDAS EXISTENTES AO INICIAR O PROGRAMA ---
    carregarVendasCSV("historico_vendas.csv"); 

    // Variáveis Locais
    char login[20];
    int senha;
    int opcaoMenu = -1;
    int opcaoAtendimento = -1;
    int opcaoVendas = -1;

    // Tela de Login
    printf("\n===================================================================\n");
    printf("|                               LANCHONETE                          |\n");
    printf("|                             WESLEY SALGADAO                       |\n"); 
    printf("===================================================================\n"); 
    printf("\nLogin de acesso: ");
    scanf("%s", login);
    limparBufferEntrada(); 

    printf("Senha: ");
    scanf("%d", &senha);
    limparBufferEntrada(); 

    // Validador de acesso
    if (strcmp(login, LOGIN_AD) == 0 && senha == SENHA_AD) {
        printf("\nACESSO PERMITIDO!\n"); 
        printf("\nPressione ENTER para continuar...");
        limparBufferEntrada(); 

        // Loop do Menu Principal
        while (opcaoMenu != 0) {
            limparTela();
            printf("\n===================================================================\n");
            printf("|                               MENU PRINCIPAL                      |\n"); 
            printf("===================================================================\n"); 
            printf("| 1 - Fazer Pedido (Atendimento ao Cliente)                       |\n"); 
            printf("| 2 - Gerenciar Vendas                                            |\n"); 
            printf("| 0 - Sair do Sistema                                             |\n"); 
            printf("-------------------------------------------------------------------\n");
            printf("Escolha uma opcao: ");
            if (scanf("%d", &opcaoMenu) != 1) { 
                printf("\nOpcao invalida. Tente novamente.\n");
                limparBufferEntrada();
                opcaoMenu = -1; 
                continue;
            }
            limparBufferEntrada(); 

            switch (opcaoMenu) {
                case 1: // Menu de Atendimento
                    opcaoAtendimento = -1;
                    while (opcaoAtendimento != 0) {
                        limparTela();
                        printf("\n===================================================================\n"); 
                        printf("|                               FAZER PEDIDO                        |\n"); 
                        printf("===================================================================\n"); 
                        printf("| 1 - Registrar Novo Pedido                                       |\n"); 
                        printf("| 2 - Exibir Cardapio                                             |\n"); 
                        printf("| 0 - Voltar ao Menu Principal                                    |\n"); 
                        printf("-------------------------------------------------------------------\n"); 
                        printf("Escolha uma opcao: ");
                        if (scanf("%d", &opcaoAtendimento) != 1) { 
                            printf("\nOpcao invalida. Tente novamente.\n");
                            limparBufferEntrada();
                            opcaoAtendimento = -1;
                            continue;
                        }
                        limparBufferEntrada(); 

                        switch (opcaoAtendimento) {
                            case 1:
                                registrarVendaComDesconto();
                                break;
                            case 2:
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
                case 2: // Menu de Gerenciamento de Vendas
                    opcaoVendas = -1;
                    while (opcaoVendas != 0) {
                        limparTela();
                        printf("\n===================================================================\n");
                        printf("|                             GERENCIAR VENDAS                      |\n"); 
                        printf("===================================================================\n");
                        printf("| 1 - Visualizar Todas as Vendas                                  |\n"); 
                        printf("| 0 - Voltar ao Menu Principal                                    |\n");
                        printf("-------------------------------------------------------------------\n"); 
                        printf("Escolha uma opcao: ");
                        if (scanf("%d", &opcaoVendas) != 1) { 
                            printf("\nOpcao invalida. Tente novamente.\n");
                            limparBufferEntrada();
                            opcaoVendas = -1;
                            continue;
                        }
                        limparBufferEntrada(); 

                        switch (opcaoVendas) {
                            case 1:
                                visualizarVendas();
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
                    // --- CHAMO A FUNÇÃO DE SALVAR AQUI, ANTES DE SAIR ---
                    salvarVendasCSV("historico_vendas.csv"); 
                    break;
                default:
                    printf("\nOpcao invalida. Tente novamente.\n");
                    break;
            }
        }
        printf("\n");
        printf("===================================================================\n");
        printf("|              SESSAO FINALIZADA COM SUCESSO!                     |\n");
        printf("|             Obrigado por utilizar o sistema!!                   |\n");
        printf("===================================================================\n"); 

    } else {
        printf("\nACESSO NEGADO - Credenciais invalidas.\n");
        printf("Por favor, contate o administrador.\n");
    }

    return 0;
}