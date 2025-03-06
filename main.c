#include <stdio.h>
#include <stdlib.h>


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
    float saldo;
    int quantidadeTransacoes;


} Conta;

void Menu();
void ExibirConta(Conta *conta);
//void Extrato(Conta conta);
//void Saque(Conta *conta);
//void Deposito(Conta *conta);

Conta CriarConta();
//Conta LogarConta(Conta conta);



int main(){
    Menu();
    int opcao = 1;
    int contaCriada = 0;
    Conta conta;

    while (opcao > 0 && opcao < 5){
        printf("\nEscolha uma Opcao : ( 0 Para Sair ) ");
        scanf("%d", &opcao);

        switch (opcao){
            case 0:
                break;

            case 1:
                conta = CriarConta();
                contaCriada = 1;
                break;

            case 2:
                if (contaCriada == 1){
                    ExibirConta(&conta);
                }
                else{
                    printf("Nenhuma Conta Cadastrada !");
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
    printf("\n-------- MENU ---------- \n");
    printf("\n[ 1 ] - Criar Conta ");
    printf("\n[ 2 ] - Realizar Login ");
    printf("\n[ 3 ] - Exibir Extrato ");
    printf("\n[ 4 ] - Realizar Saque ");
    printf("\n[ 5 ] - Realizar Deposito ");
    printf("\n[ 0 ] - Sair \n");
}


Conta CriarConta()
{
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
    printf("\n\tDigite o seu nome Completo : ");
    scanf("%s", &novaPessoa.nome);
    printf("\n\tDigite o seu CPF : ");
    scanf("%s", &novaPessoa.cpf);
    printf("\n\tDigite a data de nascimento : ");
    scanf("%s", &novaPessoa.dataNascimento);

    //Este bloco define os atributos da conta;
    novaConta.pessoaFisica = novaPessoa;
    novaConta.historico = historico;

    novaConta.idConta = 1;
    novaConta.saldo = 0;
    novaConta.quantidadeTransacoes = 0;


    return novaConta;
}


void ExibirConta(Conta *conta)
{

    printf("\n========= DADOS DA CONTA =========");
    printf("\n------------------------------------\n");

    printf("\n\tID da Conta : %d ", conta->idConta);
    printf("\n\tSaldo : %.2f \n", conta->saldo);

    printf("\n========= Dados do Usuario =========");
    printf("\n\tNome Completo : %s ", conta->pessoaFisica.nome);
    printf("\n\tCPF : %s ", conta->pessoaFisica.cpf);
    printf("\n\tData de Nascimento : %s \n", conta->pessoaFisica.dataNascimento);

}







