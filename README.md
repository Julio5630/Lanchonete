
-----

# Sistema de Gerenciamento de Lanchonete

Este é um sistema simples de gerenciamento de lanchonete desenvolvido em C. Ele permite registrar vendas, visualizar o cardápio e gerenciar o histórico de vendas, com um sistema de login para acesso.

-----

## Participantes do Projeto

Conheça os desenvolvedores deste projeto:

  * [**Erik Eike Silva**](https://github.com/ErikEikeSilva)
  * [**Massacral**](https://github.com/Massacral)
  * [**Luciana-Anascimento**](https://github.com/Luciana-Anascimento)
  * [**Julio5630**](https://github.com/Julio5630)

-----

## Funcionalidades

  * **Login de Acesso**: Sistema de autenticação para controle de acesso às funcionalidades.
  * **Cardápio Interativo**: Exibe uma lista predefinida de salgados, porções e bebidas.
  * **Registro de Pedidos**: Permite adicionar múltiplos itens a um pedido, com cálculo de subtotal e total.
  * **Desconto Automático**: Aplica um desconto de 5% em pedidos acima de R$50,00.
  * **Comprovante de Pedido**: Gera e exibe um comprovante detalhado para cada pedido finalizado.
  * **Histórico de Vendas**: Permite visualizar todas as vendas registradas, incluindo o total geral.
  * **Limpeza de Tela**: Função para manter a interface do console organizada.

-----

## Como Compilar e Rodar

Para compilar e executar este código, você precisará de um compilador C (como GCC).

1.  **Salve o código**: Salve o código-fonte como `lanchonete.c` (ou outro nome de sua preferência).

2.  **Compile o código**: Abra um terminal ou prompt de comando e execute o seguinte comando:

    ```bash
    gcc lanchonete.c -o lanchonete.exe
    ```

3.  **Execute o programa**: Após a compilação, você pode executar o programa com:

    ```bash
    ./lanchonete.exe
    ```

-----

## Credenciais de Acesso

Ao iniciar o programa, você será solicitado a fazer login. Utilize as seguintes credenciais:

  * **Login**: `admin`
  * **Senha**: `1234`

-----

## Estrutura do Código

O código é dividido em funções para melhor organização:

  * **`limparTela()`**: Limpa o console para uma melhor experiência do usuário (compatível com Windows e sistemas Unix-like).
  * **`inicializarCardapio()`**: Popula o cardápio com itens predefinidos ao iniciar o programa.
  * **`exibirCardapio()`**: Mostra a lista de todos os itens disponíveis no cardápio.
  * **`gerarComprovante()`**: Cria e exibe o comprovante de um pedido, incluindo detalhes dos itens, subtotal, desconto e total final.
  * **`registrarVendaComDesconto()`**: Gerencia o processo de registro de um novo pedido, permitindo adicionar vários itens e aplicando desconto se o subtotal for superior ao valor mínimo.
  * **`visualizarVendas()`**: Exibe um histórico detalhado de todas as vendas realizadas.
  * **`main()`**: A função principal que controla o fluxo do programa, incluindo o login, o menu principal e a navegação entre as diferentes funcionalidades.

-----

## Constantes e Estruturas

O código utiliza as seguintes constantes e estruturas para organizar os dados:

### Constantes

  * `SENHA_AD`: Senha de administrador (`1234`).
  * `LOGIN_AD`: Login de administrador (`"admin"`).
  * `MAX_ITENS_CARDAPIO`: Número máximo de itens que o cardápio pode ter (`50`).
  * `MAX_VENDAS`: Número máximo de registros de vendas que podem ser armazenados (`500`).
  * `MAX_ITENS_PEDIDO`: Número máximo de itens que um único pedido pode conter (`20`).

### Estruturas

  * **`ItemCardapio`**: Representa um item individual no cardápio.
      * `id` (int): Identificador único do item.
      * `nome` (char\[100]): Nome do item.
      * `preco` (float): Preço unitário do item.
  * **`RegistroVenda`**: Usada para registrar cada item vendido no histórico de vendas.
      * `idVenda` (int): ID da venda à qual o item pertence.
      * `idItemVendido` (int): ID do item que foi vendido.
      * `nomeItem` (char\[100]): Nome do item vendido.
      * `quantidade` (int): Quantidade vendida do item.
      * `precoUnitario` (float): Preço unitário do item no momento da venda.
      * `totalVenda` (float): Subtotal do item (quantidade \* preço unitário).
  * **`ItemPedidoAtual`**: Utilizada temporariamente para armazenar os detalhes dos itens de um pedido atual para a geração do comprovante.
      * `idItem` (int): ID do item.
      * `nomeItem` (char\[100]): Nome do item.
      * `quantidade` (int): Quantidade do item no pedido.
      * `precoUnitario` (float): Preço unitário do item.
      * `subtotalItem` (float): Subtotal do item (quantidade \* preço unitário).

-----

## Observações

  * O sistema armazena os dados em memória e não possui persistência. Ao fechar o programa, todos os dados (cardápio, vendas) são perdidos.
  * A interface é baseada em console e interage com o usuário via entrada e saída padrão.
  * O tratamento de erro para entrada do usuário é básico, garantindo que números sejam inseridos onde esperado.

-----
