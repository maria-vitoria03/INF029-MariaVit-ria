#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void moduloAlunos();

int main(void) {

  int opcao;
  int sair = 0;

  // Menu principal do programa
  while (!sair) {
    printf("******** Projeto Escola ******** \n");
    printf("0 -> Sair \n");
    printf("1 -> Módulo de alunos \n");
    printf("2 -> Módulo de professores \n");
    printf("3 -> Módulo de disciplinas\n");
    printf("4 -> Módulo de relatórios \n");
    printf("Digite sua opção: \n");
    scanf("%d", &opcao);
    system("clear");

    // Opções do menu principal
    switch (opcao) {
    case 0:
      sair = 1;
      break;
    case 1:
      moduloAlunos();
      break;
    default:
      printf("Opção Inválida!\n");
      break;
    }
  }
  return 0;
}

void moduloAlunos() {
  int opcaoAluno;
  int sairAluno = 0;
  int contAluno = 0;
  Pessoa listaAlunos[TAM];

  // Menu de alunos
  while (!sairAluno) {
    printf("******** Módulo de alunos ******** \n");
    printf("0 -> Voltar para página inicial \n");
    printf("1 -> Cadastrar Aluno \n");
    printf("2 -> Atualizar Aluno \n");
    printf("3 -> Excluir Aluno \n");
    printf("Digite sua opção: \n");
    scanf("%d", &opcaoAluno);
    system("clear");

    // Opções do menu de alunos
    switch (opcaoAluno) {
    case 0:
      sairAluno = 1;
      break;
    case 1:
      contAluno = cadastrarAlunos(listaAlunos, contAluno);
      break;
    default:
      printf("Opção Inválida! \n");
      break;
    }
  }
}