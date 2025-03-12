#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//Define a estrutura para a definicao de um cadastro de Pessoa F�sica
typedef struct
{
    int idUsuario;
    char nome[50];
    char cpf[12];
    char dataNascimento[11];

} PessoaFisica;

//Define a estrutura do Historico da conta
typedef struct
{
    char tipoTransacao[20];
    float valor;
    char data[30];

} Transacao;

typedef struct
{
    Transacao *transacoes;
    int tamanho;
    int capacidade;

} Historico;

//Define a estrutura da conta
typedef struct
{
    PessoaFisica pessoaFisica;
    Historico *historico;
    int idConta;
    char senha[20];
    float saldo;
    int quantidadeTransacoes;

} Conta;

typedef struct
{
    Conta *contas;
    int tamanho;
    int capacidade;

} ListaContas;


// Funcao que exibe o menu
void Menu();
void AdicionarConta(ListaContas *contas, Conta *conta); // Adiciona a conta criada a lista de contas

//Inicializa os ponteiros que armazenaram os arrays do Sistema
void InicializarLista(ListaContas *contas, int capacidadeInicial);
void InicializaExtrato(Historico **historico, int capacidadeInicial);

// Funcoes que exibirao informacoes ao usuario
void ExibirContas(ListaContas *listaContas);
void ExibirInformacoes(Conta *contaLogada);
void ExibirExtrato(Historico *historico);
// Funcoes de manipulacao de dados da conta do usuario
void Deslogar(Conta *contaLogada);
void Saque(Conta *contaLogada);
void Deposito(Conta *contaLogada);

//Funcoes que gerenciam funcoes do sistema
Conta CriarConta(ListaContas *listaContas);
Conta *LogarConta(ListaContas *listaContas);



int main(){
    //Exibe a mensagem de Boas Vindas e o Menu
    BemVindo();
    Menu();
    //Cria as variaveis do sistema
    int opcao = 1;
    int contaCriada = 0;
    int logStatus =  1;
    // Instancia a conta que sera utilizada pelo usuario
    Conta novaConta;
    Conta *contaLogada = NULL;

    //Inicializa a Lista de contas.
    ListaContas listaContas;
    inicializarLista(&listaContas, 2);


    while (opcao > 0 && opcao < 8){
        printf("\nEscolha uma Opcao : ( 0 Para Sair ) ");
        scanf("%d", &opcao);

        switch (opcao){
            case 0:
                break;

            case 1:
                novaConta = CriarConta(&listaContas);
                AdicionarConta(&listaContas, &novaConta);
                //Define a variavel que confirma ao menos uma conta cadastrada
                contaCriada = 1;
                break;

            if (contaCriada == 1)
            {
                case 2:
                    // Faz a chamada da funcao LogarConta para permitir o login ativo.
                    contaLogada = LogarConta(&listaContas);
                    logStatus = 1; // Altera o Status para 1, indicando um login ativo.
                    break;

                case 3:
                    ExibirContas(&listaContas); // Exibe as contas criadas.
                    break;
            }
            else{
                printf("\n Nenhuma Conta Cadastrada !");
            }

            if (logStatus == 1)
            {
                case 4:
                    ExibirInformacoes(contaLogada); // Exibe as informacoes da conta Logada.
                    break;

                case 5:
                    if (contaLogada->historico != NULL){
                        ExibirExtrato(contaLogada->historico);
                    }
                    else{
                        printf("\nNenhuma Transacao Cadastrada !\n");
                    }

                    break;

                case 6:
                    Saque(contaLogada);
                    break;

                case 7:
                    Deposito(contaLogada);
                    break;
            }
            else{
                printf("\n Nao ha Login Ativo !");
            }

            default:
                printf("\n Opcao nao Encontrada ! \n");
                break;
        }

        while (getchar() != '\n'); // Limpa o buffer de entrada, para evitar erros de leitura.
        //Limpa a tela antes de exibir o Menu novamente.
        sleep(1); // O sistema espera 3 segundos antes de limpar a tela.
        system("cls");
        Menu();
    }
    return 0;
}



void BemVindo(){
    printf("==============================\n");
    printf("======== BEM VINDO ===========\n");
    printf("========= ATM BANK ===========\n");
    printf("==============================\n");
    printf("\n");
}

void Menu()
{
    printf("\n========= MENU =========== \n");
    printf("\n[ 1 ] - Criar Conta ");
    printf("\n[ 2 ] - Realizar Login ");
    printf("\n[ 3 ] - Listar Contas ");
    printf("\n[ 4 ] - Exibir Informacoes \n");
    printf("\n------- TRANSACOES ------- ");
    printf("\n[ 5 ] - Exibir Extrato ");
    printf("\n[ 6 ] - Realizar Saque ");
    printf("\n[ 7 ] - Realizar Deposito ");
    printf("\n[ 0 ] - Sair \n");
    printf("\n========================== \n");
}


// Adiciona a conta a lista
void AdicionarConta(ListaContas *listaContas, Conta *conta){
    if (listaContas->tamanho == listaContas->capacidade){
       listaContas->capacidade *=2;
       listaContas->contas = (Conta *)realloc(listaContas->contas, listaContas->capacidade * sizeof(Conta));
       if (listaContas->contas == NULL){
        printf("Erro ao realocar mem�ria!\n");
        exit(1);
       }
    }

    listaContas->contas[listaContas->tamanho] = *conta;
    listaContas->tamanho++;
}

// Funcao responsavel por inicializar a lista de contas
void inicializarLista(ListaContas *listaContas, int capacidadeInicial) {
    listaContas->contas = (Conta *)malloc(capacidadeInicial * sizeof(Conta));
    if (listaContas->contas == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    listaContas->tamanho = 0;
    listaContas->capacidade = capacidadeInicial;
}


// Fun��o para inicializar o hist�rico de transa��es
void InicializaExtrato(Historico **historico, int capacidadeInicial) {
    *historico = (Historico *)malloc(sizeof(Historico));
    if (*historico == NULL) {
        printf("Erro ao alocar memoria para o historico!\n");
        exit(1);
    }

    (*historico)->transacoes = (Transacao *)malloc(capacidadeInicial * sizeof(Transacao));
    if ((*historico)->transacoes == NULL) {
        printf("Erro ao alocar memoria para as transa�oes!\n");
        free(*historico);
        exit(1);
    }

    (*historico)->tamanho = 0;
    (*historico)->capacidade = capacidadeInicial;
}


// Define a funcao de criar conta
Conta CriarConta(ListaContas *listaContas){
    char nome[50];
    char cpf[12];
    char dataNascimento[11];


    //Instancia a PessoaFisica
    PessoaFisica novaPessoa;

    //Instancia a Conta
    Conta novaConta;


    printf("\n\tDigite o seu nome Completo: ");
    while (getchar() != '\n');
    fgets(novaPessoa.nome, sizeof(novaPessoa.nome), stdin);
    novaPessoa.nome[strcspn(novaPessoa.nome, "\n")] = 0;

    bool valida_cpf = false;
    do {
        printf("\n\tDigite o seu CPF (apenas numeros): ");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = 0;  // Remove \n

        valida_cpf = verifica_cpf(cpf);
        if (!valida_cpf) {
            printf("\n\tCPF invalido! Tente novamente.");
        }
    } while (!valida_cpf);

    // Copia o CPF validado para a estrutura
    strcpy(novaPessoa.cpf, cpf);


    while (getchar() != '\n');
    printf("\n\tDigite a data de nascimento (DD/MM/AAAA): ");
    fgets(novaPessoa.dataNascimento, sizeof(novaPessoa.dataNascimento), stdin);
    novaPessoa.dataNascimento[strcspn(novaPessoa.dataNascimento, "\n")] = 0;

    while (getchar() != '\n');
    printf("\n\tDigite uma senha para a conta (MAX 20 caracteres): ");
    scanf("%19s", novaConta.senha);


    novaConta.pessoaFisica = novaPessoa;
    // Inicializa o Extrato
    InicializaExtrato(&novaConta.historico, 3);

    novaConta.idConta = listaContas->tamanho + 1;
    novaConta.saldo = 0;
    novaConta.quantidadeTransacoes = 0;


    printf("\nConta Criada com Sucesso ! ");

    return novaConta;
}


Conta *LogarConta(ListaContas *listaContas) {
    char senha[20];
    char cpf[11];

    printf("Digite o CPF (Somente Numeros): ");
    while (getchar() != '\n');
    scanf("%s", cpf);


    for (int i = 0; i < listaContas->tamanho; i++) {
        if (strcmp(cpf, listaContas->contas[i].pessoaFisica.cpf) == 0) {
            printf("Cadastro Encontrado!\n");
            printf("Digite a senha: ");
            scanf("%s", senha);

            if (strcmp(senha, listaContas->contas[i].senha) == 0) {
                printf("Login Confirmado!\n");
                return &listaContas->contas[i];  // Retorna ponteiro para a conta
            } else {
                printf("Senha Incorreta!\n");
                return NULL;
            }
        }
    }

    printf("Conta nao Encontrada!\n");
    sleep(2);
    return NULL;
}


void ExibirContas(ListaContas *listaContas) {
    if (listaContas->tamanho == 0) {
        printf("\nNenhuma conta cadastrada!\n");
        return;
    }

    printf("\n            LISTA DE CONTAS ");
    for (int i = 0; i < listaContas->tamanho; i++) {
        Conta *conta = &listaContas->contas[i];

        printf("\n\tID da Conta : %d ", conta->idConta);
        printf("\n\tSaldo : %.2f \n", conta->saldo);
        printf("\n          Dados do Usuario            ");
        printf("\n\tNome Completo : %s ", conta->pessoaFisica.nome);
        printf("\n\tCPF : %s ", conta->pessoaFisica.cpf);
        printf("\n\tData de Nascimento : %s \n", conta->pessoaFisica.dataNascimento);
        printf("\n============================================");
    }
    sleep(1);
}


void ExibirInformacoes(Conta *contaLogada){
    printf("\n           DADOS DA CONTA          \n");
    printf("\n\tID da Conta : %d ", contaLogada->idConta);
    printf("\n\tSaldo : %.2f \n", contaLogada->saldo);
    printf("\n           Dados do Usuario          \n");
    printf("\n\tNome Completo : %s ", contaLogada->pessoaFisica.nome);
    printf("\n\tCPF : %s ", contaLogada->pessoaFisica.cpf);
    printf("\n\tData de Nascimento : %s \n", contaLogada->pessoaFisica.dataNascimento);
    printf("\n============================================");

    sleep(1);
}


void ExibirExtrato(Historico *historico){
    for (int i=0; i<historico->tamanho; i++){
        printf("      EXTRATO     ");
        printf("\nTipo de Transacao: %s ", historico->transacoes[i].tipoTransacao);
        printf("\nData da Transacao: %s ", historico->transacoes[i].data);
        printf("\nvalor : %.2f ", historico->transacoes[i].valor);
        printf("\n---------------------------\n");
    }
}


void Deposito(Conta *contaLogada){
    float valor;
    char confirmar;
    printf("\n      DEPOSITO     ");
    while (getchar() != '\n');
    printf("\nInforme o valor do Deposito : ");
    scanf("%f", &valor);

    if (valor > 0){
        printf("\n Valor : %.2f", valor);
        while (getchar() != '\n');
        printf("\n Confirmar Deposito  (s/n)?");
        scanf("%c", &confirmar);

        if(confirmar == 's' || confirmar == 'S'){
            contaLogada->saldo += valor;
            printf("\n Saldo Realizado com Sucesso !");
            printf("\n Saldo : %.2f ", contaLogada->saldo);

        // Insere os dados da transacao ao Extrato
        Transacao deposito;


        // Obt�m a data e hora atual corretamente
        time_t tempoAtual = time(NULL);
        struct tm *tm_info = localtime(&tempoAtual);

        if (tm_info != NULL) {
            sprintf(deposito.data, "%02d/%02d/%04d %02d:%02d:%02d",
                    tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
        } else {
            strcpy(deposito.data, "ERRO");
        }

        deposito.valor = valor;
        strcpy(deposito.tipoTransacao, "Deposito");
        contaLogada->historico->transacoes[contaLogada->historico->tamanho] = deposito;
        contaLogada->historico->tamanho++;

        }
        else{
            printf("\n Operacao Cancelada !");
        }
    }

}


void Saque(Conta *contaLogada){
    float valor;
    char confirmar;
    printf("\n      SAQUE     ");
    while (getchar() != '\n');
    printf("\nInforme o valor do Saque : ");
    scanf("%f", &valor);

    if (valor > 0 && contaLogada->saldo >= valor){
        printf("\n Valor : %.2f", valor);
        while (getchar() != '\n');
        printf("\n Confirmar Saque  (s/n)?");
        scanf("%c", &confirmar);

        if(confirmar == 's' || confirmar == 'S'){
            contaLogada->saldo -= valor;
            printf("\n Saldo Realizado com Sucesso !");
            printf("\n Saldo : %.2f ", contaLogada->saldo);

        // Insere os dados da transacao ao Extrato
        Transacao saque;

        // Obt�m a data e hora atual corretamente
        time_t tempoAtual = time(NULL);
        struct tm *tm_info = localtime(&tempoAtual);

        if (tm_info != NULL) {
            sprintf(saque.data, "%02d/%02d/%04d %02d:%02d:%02d",
                    tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
        } else {
            strcpy(saque.data, "ERRO");
        }

        saque.valor = valor;
        strcpy(saque.tipoTransacao, "Saque");
        contaLogada->historico->transacoes[contaLogada->historico->tamanho] = saque;
        contaLogada->historico->tamanho++;

        }
        else{
            printf("\n Operacao Cancelada !");
        }
    }
    else{
        printf("\n Saldo Insuficiente ! \n");
    }

}


