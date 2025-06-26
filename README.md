
# 🚗 Sistema de Gerenciamento para Clínica Habilitar 🚦

<div align="center">
  <img src="[https://placehold.co/800x300](https://www.google.com/url?sa=i&url=http%3A%2F%2Fciateatrosolidario.blogspot.com%2F2010%2F08%2Fmulher-no-volante-perigo-constante.html&psig=AOvVaw0Jcbxac-H6KmmVMVl-dMk4&ust=1751056305505000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCPixuf32j44DFQAAAAAdAAAAABAE)" alt="Banner mostrando um sistema de gestão de CNH com interface moderna, contendo elementos de trânsito e formulários digitais em tons de azul e verde" />
  <br>
  
  ![GitHub last commit](https://img.shields.io/github/last-commit/usuario/clinica-habilitar?style=flat-square)
  ![GitHub repo size](https://img.shields.io/github/repo-size/usuario/clinica-habilitar?color=success&style=flat-square)
  ![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)
</div>

## 📚 Informações do Projeto

**SENAC DF – Centro de Educação Profissional Jó Rufino e Carlos Aguiar – Taguatinga**  
**Curso:** Técnico em Desenvolvimento de Sistemas  
**Turma:** 2025.08.53  
**Unidade Curricular:** UC 4 – Analisar Programação Estruturada e Orientada a Objetos  
**Professor Orientador:** Hudson Neves  

**Aluno(a):** [Seu nome completo]  
**Data:** [Data de entrega ou elaboração do trabalho]  

## 👥 Equipe de Desenvolvimento

* [**Erik Eike Silva**](https://github.com/ErikEikeSilva)
* [**Massacral**](https://github.com/Massacral)
* [**Luciana-Anascimento**](https://github.com/Luciana-Anascimento)
* [**Julio5630**](https://github.com/Julio5630)

## ✨ Visão Geral

Um sistema completo para gestão de processos de habilitação veicular, desenvolvido em C com foco em:

- 👥 Controle de clientes
- 📝 Gerenciamento de processos
- 📊 Geração de relatórios
- 🔒 Acesso seguro

## 🛠️ Funcionalidades Principais

| Módulo          | Descrição                                                                 | Status       |
|-----------------|---------------------------------------------------------------------------|-------------|
| 📋 Cadastro     | Registro completo de clientes com validação de dados                      | ✅ Completo  |
| 🔍 Consulta     | Busca ágil por CPF com exibição detalhada                                 | ✅ Completo  |
| 📈 Relatórios   | Listagem organizada de todos os processos                                 | ✅ Completo  |
| 🔄 Atualização  | Modificação de status dos processos                                       | ✅ Completo  |
| 💾 Persistência | Armazenamento em arquivo para manutenção dos dados                        | ✅ Completo  |

## 🖥️ Pré-visualização da Interface

<div align="center">
  <img src="https://placehold.co/600x400" alt="Captura de tela mostrando o menu principal do sistema com opções numeradas em formato tabela, simulando interface de terminal" />
</div>

## ⚙️ Tecnologias Utilizadas

```mermaid
flowchart TD
    Start([Início])
    Login[Inserir informações de login]
    VerificaDados{Dados corretos?}
    Erro[Dados inseridos<br>estão incorretos]
    Menu[Menu inicial]
    Encerrar[Encerrar o sistema]
    End([Fim])

    Start --> Login --> VerificaDados
    VerificaDados -- Não --> Erro --> Login
    VerificaDados -- Sim --> Menu
    Menu --> Encerrar --> End

    %% Opção 1
    Menu --> |Opção 1| Proc[ Abertura de<br> Processos ]
    Proc --> Nome[Solicitar Nome<br>Completo]
    Nome --> CPF1[Solicitar CPF]
    CPFValido1{CPF válido?}
    CPF1 --> CPFValido1
    CPFValido1 -- Não --> CPF1
    CPFValido1 -- Sim --> Idade[Solicitar Idade]
    IdadeValida{Idade ≥ 18?}
    Idade --> IdadeValida
    IdadeValida -- Não --> Idade
    IdadeValida -- Sim --> Categoria[Selecionar categoria desejada]
    Categoria --> A

    %% Opção 2
    Menu --> |Opção 2| Relatorio[Relatório de atendimentos]
    Relatorio --> ListarRel[Listar Todos os Relatórios]
    ListarRel --> A

    %% Opção 3
    Menu --> |Opção 3| Consulta[Consultar processos<br>por CPF]
    Consulta --> CPF2[Solicitar CPF]
    CPF2 --> Exibir1[Exibir Processo Solicitado]
    Exibir1 --> A

    %% Opção 4
    Menu --> |Opção 4| Atualizar[Atualizar status do processo]
    Atualizar --> CPF3[Solicitar CPF]
    CPF3 --> Exibir2[Exibir Processo Solicitado]
    Exibir2 --> NovoStatus[Solicitar o novo status<br>para o processo]
    NovoStatus --> Salvar[Salvar atualização dos dados]
    Salvar --> A

    %% Ponto de retorno ao menu
    A((A)) --> Menu

```

## 📦 Requisitos e Instalação

### Pré-requisitos
- GCC (compilador C)
- Terminal Linux/Windows

### Passo a passo
```bash
# Clone o repositório
git clone https://github.com/usuario/clinica-habilitar.git

# Acesse o diretório
cd clinica-habilitar

# Compile o programa
gcc sistema_habilitar.c -o sistema_habilitar.exe

# Execute
./sistema_habilitar.exe
```

## 🔐 Credenciais de Acesso
```plaintext
Usuário: admin
Senha: 1234 
```

## 📚 Documentação Técnica

### Estrutura do Projeto
```
clinica-habilitar/
├── sistema_habilitar.c  # Código fonte principal
├── clientes_cnh.txt     # Banco de dados de clientes
└── README.md            # Documentação
```

### Validações Implementadas
- ✔️ CPF (formato e dígitos)
- ✔️ Idade mínima (18 anos)
- ✔️ Categorias de CNH válidas
- ✔️ Tipos de serviço permitidos

## 🚦 Próximas Implementações
- [ ] Módulo financeiro
- [ ] Interface gráfica
- [ ] Backup automático
