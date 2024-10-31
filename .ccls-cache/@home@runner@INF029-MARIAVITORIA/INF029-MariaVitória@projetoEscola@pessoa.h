#ifndef PESSOA_H
#define PESSOA_H

#define TAM 3

typedef struct {
    int matricula;
    char nome[100];
    char sexo;
    char dataNasc[10];
    char cpf[15];
    int ativo;
}Pessoa;

int cadastrarAlunos(Pessoa lista[TAM], int contador);
void atualizarAlunos();

#endif // PESSOA_H