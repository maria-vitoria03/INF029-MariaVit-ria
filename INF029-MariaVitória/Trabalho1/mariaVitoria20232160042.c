// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Maria Vitória Santos da Silva 
//  email: mariavitoriaprog@gmail.com
//  Matrícula: 20232160042
//  Semestre: 2º

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "mariavitoria20232160042.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

DataQuebrada quebraData(char data[]);

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
    int datavalida = 1;
    int vetMesesUm[7] = {1, 3, 5, 7, 8, 10, 12}; // Meses com 31 dias
    int vetMesesDois[4] = {4, 6, 9, 11};         // Meses com 30 dias

    DataQuebrada verifica;
    verifica = quebraData(data);  // Quebra a string data em iDia, iMes, iAno

    // Verificação do intervalo do mês
    if (verifica.iMes < 1 || verifica.iMes > 12) {
        return 0;
    }

    // Verificação do intervalo dos dias
    if (verifica.iDia < 1 || verifica.iDia > 31) {
        return 0;
    }

    // Verificação dos dias dos meses com 31 dias
    int i;
    for (i = 0; i < 7; i++) {
        if (verifica.iMes == vetMesesUm[i]) {
            if (verifica.iDia > 31) {
                return 0;
            }
            return datavalida; // Retorno válido para meses com 31 dias
        }
    }

    // Verificação dos dias dos meses com 30 dias
    for (i = 0; i < 4; i++) {
        if (verifica.iMes == vetMesesDois[i]) {
            if (verifica.iDia > 30) {
                return 0;
            }
            return datavalida; // Retorno válido para meses com 30 dias
        }
    }

    // Verificação do mês de fevereiro
    int bissexto = (verifica.iAno % 4 == 0 && (verifica.iAno % 100 != 0 || verifica.iAno % 400 == 0));

    if (verifica.iMes == 2) {
        
        if ((bissexto && verifica.iDia > 29) || (!bissexto && verifica.iDia > 28)) {
            return 0;
        }
    }

    // Se todas as condições forem atendidas, a data é válida
    return datavalida;
}

int diasNoMes(int mes, int ano) {
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Verifica se é fevereiro em ano bissexto
    if (mes == 2 && (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))) {
        return 29;
    }
    return diasPorMes[mes - 1];
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
    DiasMesesAnos dma = {0, 0, 0, 0};
    DataQuebrada dataInicial;
    DataQuebrada dataFinal;

    // Validação das datas
    if (q1(datainicial) == 0) {
        dma.retorno = 2; // Data inicial inválida
        return dma;
    } else if (q1(datafinal) == 0) {
        dma.retorno = 3; // Data final inválida
        return dma;
    }

    // Quebra as datas em dia, mês e ano
    dataInicial = quebraData(datainicial);
    dataFinal = quebraData(datafinal);

    // Corrige anos com dois dígitos
    if (dataFinal.iAno < 100) dataFinal.iAno += 2000;
    if (dataInicial.iAno < 100) dataInicial.iAno += 2000;

    // Verifica se a data final não é menor que a inicial
    if (dataFinal.iAno < dataInicial.iAno ||
        (dataFinal.iAno == dataInicial.iAno && dataFinal.iMes < dataInicial.iMes) ||
        (dataFinal.iAno == dataInicial.iAno && dataFinal.iMes == dataInicial.iMes && dataFinal.iDia < dataInicial.iDia)) {
        dma.retorno = 4; // Data final é menor que a inicial
        return dma;
    }

    // Ajusta os dias
    if (dataFinal.iDia < dataInicial.iDia) {
        dataFinal.iDia += diasNoMes(dataFinal.iMes == 1 ? 12 : dataFinal.iMes - 1, 
                                    dataFinal.iMes == 1 ? dataFinal.iAno - 1 : dataFinal.iAno);
        dataFinal.iMes -= 1;
        if (dataFinal.iMes == 0) {
            dataFinal.iMes = 12;
            dataFinal.iAno -= 1;
        }
    }
    dma.qtdDias = dataFinal.iDia - dataInicial.iDia;

    // Ajusta os meses
    if (dataFinal.iMes < dataInicial.iMes) {
        dataFinal.iMes += 12;
        dataFinal.iAno -= 1;
    }
    dma.qtdMeses = dataFinal.iMes - dataInicial.iMes;

    // Calcula os anos
    dma.qtdAnos = dataFinal.iAno - dataInicial.iAno;

    // Cálculo realizado com sucesso
    dma.retorno = 1;
    return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive) {
    int qtdOcorrencias = 0;

    if (!isCaseSensitive) {
        c = toupper(c);
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        char currentChar = texto[i];

        if (!isCaseSensitive) {
            currentChar = toupper(currentChar);
        }

        if (currentChar == c) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30]) {
    int qtdOcorrencias = 0; 
    int tamTexto = strlen(strTexto);
    int tamBusca = strlen(strBusca);
    int posIndex = 0;

    for (int i = 0; i <= tamTexto - tamBusca; i++) {
        int encontrado = 1; 

        for (int j = 0; j < tamBusca; j++) {
            if (strTexto[i + j] != strBusca[j]) {
                encontrado = 0; 
                break;
            }
        }

        if (encontrado) {
            posicoes[posIndex++] = i + 1;
            posicoes[posIndex++] = i + tamBusca;
            qtdOcorrencias++;
        }
    }
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
    #define MAX 50

    int vet[MAX];
    int i = 0, invertido = 0;

    while (num > 0) {
        vet[i] = num % 10;
        num /= 10;
        i++;
    }

    for (int j = 0; j < i; j++) {
        invertido = invertido * 10 + vet[j];
    }

    return invertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */
int q6(int numerobase, int numerobusca) {
    int qtdOcorrencias = 0;

    int tamanhoBusca = 1;
    int tempBusca = numerobusca;
    while (tempBusca >= 10) {
        tamanhoBusca *= 10;
        tempBusca /= 10;
    }

    while (numerobase > 0) {

        int trecho = numerobase % (tamanhoBusca * 10);

        if (trecho == numerobusca) {
            qtdOcorrencias++;

            numerobase /= tamanhoBusca;
        } else {
            numerobase /= 10;
        }
    }

    return qtdOcorrencias;
}

DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia); //mm/08/2000
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);
    dq.valido = 1; 
    
  return dq;
}

