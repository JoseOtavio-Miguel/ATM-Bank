#include <stdio.h>
#include <stdbool.h>
#include <string.h>  // Para strlen
#include "util.h"

bool verifica_cpf(char cpf[]) {
    int cpf_9digitos[9];
    int digitos_verificador[2];
    int contador = 10;
    int resultados = 0;
    int resto_divisao;

    // Verifica se o CPF tem 11 caracteres
    if (strlen(cpf) != 11) {
        printf("\nErro: CPF deve ter exatamente 11 digitos!\n");
        return false;
    }

    // Converte os primeiros 9 d�gitos para inteiros
    for (int i = 0; i < 9; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') {  // Verifica se � n�mero
            printf("\nErro: CPF deve conter apenas n�meros!\n");
            return false;
        }
        cpf_9digitos[i] = cpf[i] - '0';
    }

    // Converte os dois �ltimos caracteres para inteiros
    digitos_verificador[0] = cpf[9] - '0';
    digitos_verificador[1] = cpf[10] - '0';

    // C�lculo do primeiro d�gito verificador
    for (int i = 0; i < 9; i++) {
        resultados += cpf_9digitos[i] * contador;
        contador--;
    }

    resto_divisao = resultados % 11;
    // Calcula o primeiro digito verificador
    int primeiro_dv = (resto_divisao < 2) ? 0 : 11 - resto_divisao;

    // C�lculo do segundo d�gito verificador
    contador = 11;
    resultados = 0;
    for (int i = 0; i < 9; i++) {
        resultados += cpf_9digitos[i] * contador;
        contador--;
    }
    resultados += primeiro_dv * contador;

    resto_divisao = resultados % 11;
    // Calcula o segundo digito verificador
    int segundo_dv = (resto_divisao < 2) ? 0 : 11 - resto_divisao;

    //printf("\nDigitos Calculados: %d %d", primeiro_dv, segundo_dv);

    // Compara��o correta com os d�gitos informados
    if (primeiro_dv == digitos_verificador[0] && segundo_dv == digitos_verificador[1]) {
        printf("\nCPF Valido!\n");
        return true;
    } else {
        printf("\nCPF Invalido!\n");
        return false;
    }
}

