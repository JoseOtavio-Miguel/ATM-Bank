# ATM Bank - Sistema de Gestão de Contas Bancárias

## Descrição
Este projeto consiste em um sistema de gerenciamento de contas bancárias, desenvolvido em C, que permite a criação de contas, realização de depósitos, saques, visualização de extratos e informações da conta. O sistema também oferece funcionalidades de login e gerenciamento de transações, proporcionando uma interface interativa e segura para o usuário.

## Funcionalidades

- **Criação de Conta**: Permite o cadastro de uma nova conta bancária, incluindo dados pessoais como nome, CPF, data de nascimento e senha.
- **Login Seguro**: Sistema de login utilizando CPF e senha para acessar as contas bancárias.
- **Realização de Depósitos e Saques**: O sistema possibilita realizar depósitos e saques, atualizando o saldo e registrando as transações no extrato.
- **Visualização de Extrato**: Exibe um extrato detalhado de todas as transações realizadas, com informações sobre o tipo de transação, valor e data.
- **Exibição de Informações da Conta**: Permite ao usuário visualizar as informações cadastrais da sua conta, incluindo saldo e dados pessoais.
- **Gestão de Conta**: O sistema permite ao usuário se deslogar da conta atual.

## Estrutura do Arquivo
O código fonte está organizado em diversas funções que são responsáveis por implementar cada uma das funcionalidades do sistema. A seguir, algumas partes principais do código:

- **Conta**: Estrutura que armazena os dados da conta bancária, incluindo dados pessoais, saldo, transações e histórico.
- **PessoaFisica**: Estrutura que armazena os dados do usuário, como nome, CPF e data de nascimento.
- **Transacao**: Estrutura que armazena os detalhes de cada transação (depósito ou saque), incluindo tipo de transação, valor e data.
- **Historico**: Estrutura que contém um array de transações, representando o extrato da conta.
- **ListaContas**: Estrutura que armazena todas as contas criadas no sistema.


## Autor
Desenvolvido por **José Otávio Miguel**.

## Licença
Este projeto está sob a **Licença MIT**.
