<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define a estrutura para a definicao de um cadastro de Pessoa Física
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
    char tipoTransacao;
    float valor;
    char data[11];

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



void Menu();
void InicializarLista(ListaContas *contas, int capacidadeInicial);
void AdicionarConta(ListaContas *contas, Conta *conta);
void ExibirContas(ListaContas *listaContas);
void ExibirInformacoes(Conta *contaLogada);
void Deslogar(Conta *contaLogada);
//void Extrato(Conta conta);
//void Saque(Conta *conta);
//void Deposito(Conta *conta);

Conta CriarConta(ListaContas *listaContas);
Conta *LogarConta(ListaContas *listaContas);



int main(){
    Menu();
    int opcao = 1;
    int contaCriada = 0;
    int logStatus =  1;
    Conta novaConta;
    Conta *contaLogada = NULL;

    //Inicializa a Lista de contas.
    ListaContas listaContas;
    inicializarLista(&listaContas, 2);


    while (opcao > 0 && opcao < 7){
        printf("\nEscolha uma Opcao : ( 0 Para Sair ) ");
        scanf("%d", &opcao);

        switch (opcao){
            case 0:
                break;

            case 1:
                novaConta = CriarConta(&listaContas);
                AdicionarConta(&listaContas, &novaConta);
                contaCriada = 1;
                break;

            case 2:
                if(contaCriada == 1){
                    // Faz a chamada da funcao LogarConta para permitir o login ativo.
                    contaLogada = LogarConta(&listaContas);
                    logStatus = 1; // Altera o Status para 1, indicando um login ativo.
                }
                else if (logStatus == 1){
                    // Permite ao usuario deslogar da conta.
                    //Deslogar(contaLogada);
                }
                else{
                    printf("Nenhuma conta Cadastrada !");
                }
                break;

            case 3:
                if (contaCriada == 1){
                    ExibirContas(&listaContas); // Exibe as contas criadas.
                }
                else{
                    printf("Nenhuma Conta Cadastrada !");
                }
                break;

            case 4:
                if (contaLogada != NULL){
                    ExibirInformacoes(contaLogada); // Exibe as informacoes da conta Logada.
                }
                else{
                    printf(" Nao ha login Ativo ! \n");
                }
                break;

            default:
                // Imprime opcao nao encontrada caso a entrada nao esteja listada.
                printf(" Opcao nao Encontrada");
                break;
        }


        while (getchar() != '\n'); // Limpa o buffer de entrada, para evitar erros de leitura.
        //Limpa a tela antes de exibir o Menu novamente.
        sleep(3); // O sistema espera 3 segundos antes de limpar a tela.
        system("cls");
        Menu();
    }
    return 0;
}





void Menu()
{
    printf("==============================\n");
    printf("======== BEM VINDO ===========\n");
    printf("========= ATM BANK ============\n");
    printf("==============================\n");
    printf("\n");
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


// Funcao responsavel por inicializar a lista de contas
void inicializarLista(ListaContas *listaContas, int capacidadeInicial) {
    listaContas->contas = (Conta *)malloc(capacidadeInicial * sizeof(Conta));
    if (listaContas->contas == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    listaContas->tamanho = 0;
    listaContas->capacidade = capacidadeInicial;
}


// Adiciona a conta a lista
void AdicionarConta(ListaContas *listaContas, Conta *conta){
    if (listaContas->tamanho == listaContas->capacidade){
       listaContas->capacidade *=2;
       listaContas->contas = (Conta *)realloc(listaContas->contas, listaContas->capacidade * sizeof(Conta));
       if (listaContas->contas == NULL){
        printf("Erro ao realocar memória!\n");
        exit(1);
       }
    }

    listaContas->contas[listaContas->tamanho] = *conta;

    listaContas->tamanho++;
}

// Define a funcao de criar conta
Conta CriarConta(ListaContas *listaContas){
    char nome[50];
    char cpf[11];
    char dataNascimento[11];


    //Instancia a PessoaFisica
    PessoaFisica novaPessoa;

    //Cria o ponteiro que recebe o local onde esta armazenado o historico da conta
    Historico *historico;

    //Instancia a Conta
    Conta novaConta;


    printf("\n\tDigite o seu nome Completo: ");
    while (getchar() != '\n');
    fgets(novaPessoa.nome, sizeof(novaPessoa.nome), stdin);
    novaPessoa.nome[strcspn(novaPessoa.nome, "\n")] = 0;

    while (getchar() != '\n');
    printf("\n\tDigite o seu CPF (apenas numeros): ");
    fgets(novaPessoa.cpf, sizeof(novaPessoa.cpf), stdin);
    novaPessoa.cpf[strcspn(novaPessoa.cpf, "\n")] = 0;

    while (getchar() != '\n');
    printf("\n\tDigite a data de nascimento (DD/MM/AAAA): ");
    fgets(novaPessoa.dataNascimento, sizeof(novaPessoa.dataNascimento), stdin);
    novaPessoa.dataNascimento[strcspn(novaPessoa.dataNascimento, "\n")] = 0;

    while (getchar() != '\n');
    printf("\n\tDigite uma senha para a conta (MAX 20 caracteres): ");
    scanf("%19s", novaConta.senha);


    novaConta.pessoaFisica = novaPessoa;
    novaConta.historico = historico;

    novaConta.idConta = listaContas->tamanho + 1;
    novaConta.saldo = 0;
    novaConta.quantidadeTransacoes = 0;

    printf("\nConta Criada com Sucesso ! ");


    return novaConta;
}


Conta *LogarConta(ListaContas *listaContas) {
    char senha[20];
    char cpf[11];

    printf("Digite o CPF (Somente Números): ");
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
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define a estrutura para a definicao de um cadastro de Pessoa Física
typedef struct
{
    int idUsuario;
    char nome[50];
    char cpf[11];
    char dataNascimento[11];

} PessoaFisica;

//Define a estrutura do Historico da conta
typedef struct
{
    char tipoTransacao;
    float valor;
    char data[11];

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



void Menu();
void InicializarLista(ListaContas *contas, int capacidadeInicial);
void AdicionarConta(ListaContas *contas, Conta *conta);
void ExibirContas(ListaContas *listaContas);
void ExibirInformacoes(Conta *contaLogada);
//void Extrato(Conta conta);
//void Saque(Conta *conta);
//void Deposito(Conta *conta);

Conta CriarConta(ListaContas *listaContas);
Conta *LogarConta(ListaContas *listaContas);



int main(){
    Menu();
    int opcao = 1;
    int contaCriada = 0;
    Conta novaConta;
    Conta *contaLogada = NULL;

    //Inicializa a Lista de contas
    ListaContas listaContas;
    inicializarLista(&listaContas, 2);


    while (opcao > 0 && opcao < 7){
        printf("\nEscolha uma Opcao : ( 0 Para Sair ) ");
        scanf("%d", &opcao);

        switch (opcao){
            case 0:
                break;

            case 1:
                novaConta = CriarConta(&listaContas);
                AdicionarConta(&listaContas, &novaConta);
                contaCriada = 1;
                break;

            case 2:
                if(contaCriada == 1){
                    contaLogada = LogarConta(&listaContas);
                }
                else{
                    printf("Nenhuma conta Cadastrada !");
                }

            case 3:
                if (contaCriada == 1){
                    ExibirContas(&listaContas);
                }
                else{
                    printf("Nenhuma Conta Cadastrada !");
                }
            case 4:
                if (contaLogada != NULL){
                    ExibirInformacoes(&contaLogada);
                }
                else{
                    printf(" Nao ha login Ativo ! \n");
                }

            default:
                break;
        }

        while (getchar() != '\n');
        sleep(3);
        system("cls");
        Menu();
    }
    return 0;
}





void Menu()
{
    printf("==============================\n");
    printf("======== BEM VINDO ===========\n");
    printf("========= ATM BANK ============\n");
    printf("==============================\n");
    printf("\n");
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



void inicializarLista(ListaContas *listaContas, int capacidadeInicial) {
    listaContas->contas = (Conta *)malloc(capacidadeInicial * sizeof(Conta));
    if (listaContas->contas == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    listaContas->tamanho = 0;
    listaContas->capacidade = capacidadeInicial;
}



void AdicionarConta(ListaContas *listaContas, Conta *conta){
    if (listaContas->tamanho == listaContas->capacidade){
       listaContas->capacidade *=2;
       listaContas->contas = (Conta *)realloc(listaContas->contas, listaContas->capacidade * sizeof(Conta));
       if (listaContas->contas == NULL){
        printf("Erro ao realocar memória!\n");
        exit(1);
       }
    }

    listaContas->contas[listaContas->tamanho] = *conta;

    listaContas->tamanho++;
}


Conta CriarConta(ListaContas *listaContas){
    char nome[50];
    char cpf[11];
    char dataNascimento[11];


    //Instancia a PessoaFisica
    PessoaFisica novaPessoa;

    //Instancia o historico
    Historico *historico;

    //Insatncia a Conta
    Conta novaConta;

    //Este bloco define os atributos da PessoaFisica
    printf("\n\tDigite o seu nome Completo: ");
    while (getchar() != '\n');
    scanf("%49s", novaPessoa.nome);

    printf("\n\tDigite o seu CPF: ");
    while (getchar() != '\n');
    scanf("%10s", novaPessoa.cpf);

    printf("\n\tDigite a data de nascimento (DD/MM/AAAA): ");
    while (getchar() != '\n');
    scanf("%10s", novaPessoa.dataNascimento);


    printf("\n\tDigite uma senha para a conta (MAX 20 caracteres): ");
    while (getchar() != '\n');
    scanf("%19s", novaConta.senha);

    novaConta.pessoaFisica = novaPessoa;
    novaConta.historico = historico;

    novaConta.idConta = listaContas->tamanho + 1;
    novaConta.saldo = 0;
    novaConta.quantidadeTransacoes = 0;

    printf("\nConta Criada com Sucesso ! ");


    return novaConta;
}


Conta *LogarConta(ListaContas *listaContas) {
    char senha[20];
    char cpf[11];

    printf("Digite o CPF (Somente Números): ");
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

    printf("\n========= LISTA DE CONTAS =========\n");
    for (int i = 0; i < listaContas->tamanho; i++) {
        Conta *conta = &listaContas->contas[i];

        printf("\n------------------------------------\n");
        printf("\n\tID da Conta : %d ", conta->idConta);
        printf("\n\tSaldo : %.2f \n", conta->saldo);
        printf("\n========= Dados do Usuario =========");
        printf("\n\tNome Completo : %s ", conta->pessoaFisica.nome);
        printf("\n\tCPF : %s ", conta->pessoaFisica.cpf);
        printf("\n\tData de Nascimento : %s \n", conta->pessoaFisica.dataNascimento);
    }
}


void ExibirInformacoes(Conta *contaLogada){

}
>>>>>>> 6bd4ff920e10fe63895c87b0ca55cef177b5b792
