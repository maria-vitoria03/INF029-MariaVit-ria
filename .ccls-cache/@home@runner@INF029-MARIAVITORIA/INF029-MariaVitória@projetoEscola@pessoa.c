#include <stdio.h>
#include <string.h>
#include "pessoa.h"
#include <stdlib.h>

// Função para cadastrar alunos
int cadastrarAlunos(Pessoa lista[], int contador) {
    if (contador == TAM) {
        printf("Lista de alunos cheia! \n");
        return contador;
    }

    // Cadastro de matrícula
    printf("Informe a matrícula do estudante: \n");
    int matAluno;
    scanf("%d", &matAluno);
    getchar(); // Limpa o buffer do scanf
    system("clear");

    if (matAluno <= 0) {
        printf("Matrícula Inválida! \n");
        return contador;
    }

    // Armazena a matrícula
    lista[contador].matricula = matAluno;

    // Cadastro de nome
    printf("Informe o nome: \n");
    fgets(lista[contador].nome, sizeof(lista[contador].nome), stdin);
    system("clear");
    lista[contador].nome[strcspn(lista[contador].nome, "\n")] = '\0';

    // Cadastro de sexo
    printf("Informe o sexo do estudante - f ou m: \n");
    char sexo;
    scanf("%c", &sexo);
    getchar(); // Limpa o buffer do scanf
    system("clear");

    if (sexo != 'f' && sexo != 'F' && sexo != 'm' && sexo != 'M') {
        printf("Sexo inválido! \n");
        return contador;
    }

    // Armazena o sexo
    lista[contador].sexo = sexo;

    // Cadastro de data de nascimento
    printf("Informe a data de nascimento no formato dd/mm/aaaa: \n");
    fgets(lista[contador].dataNasc, sizeof(lista[contador].dataNasc), stdin);
    system("clear");
    lista[contador].dataNasc[strcspn(lista[contador].dataNasc, "\n")] = '\0';
    getchar();
    // Cadastro de CPF
    printf("Informe o CPF no formato 000.000.000-00: \n");
    getchar();
    fgets(lista[contador].cpf, sizeof(lista[contador].cpf), stdin);
    system("clear");
    lista[contador].cpf[strcspn(lista[contador].cpf, "\n")] = '\0';
    printf("Estudante matriculado com sucesso! \n\n");

    return contador + 1;
}

// Função para atualizar alunos
// void atualizarAlunos(){
// }