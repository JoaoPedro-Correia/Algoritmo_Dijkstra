//!!AS VARIAVEIS QUE ARMAZENAM A MATRICULA SÃO CHAMADAS DE 'ID'

/*PRE-PROCESSAMENTO DAS FUNCOES IMPORTADAS*/
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*CHAMO A BIBLIOTECA DA LISTA*/
/*list.h TEM DUAS ESTRUTURAS,
 * NODE E LIST*/
#include "cidades.h"
#include "list.h"
#include "node.c"

int menu(void);

long int contar_linhas(char *file_name);
/*ADICIONO O ESTUDANTE DO ARQUIVO NA LISTA*/
void get_file_element(List *l, FILE *fl, int n, int origem);
/*LER AQUIVO*/
void read_file(List *, char *, long int); // Lista e o NOME do arquivo
/*PRINTA TODOS OS ELEMENTOS DA LISTA*/
void list_print(List *l);
/*EXIBE A LISTA NA TELA EM SUA POSIÇÃO NA TABELA HASH*/
void printList(List *list);

void escolherCidadeInicial(List *list, int *menorCaminho);

void printListaCidades();

void buscarMenorCaminho(List *, float *, int *, int *, int, int);

void geraCaminho(float *estimativa, int *precedente, int origem, int destino);

int encontrarMenorVertice(List *list, float *estimativa, int *finalizado);

void dijikstra(List *list);

int lines;
/*------------------------------------------------------------*/
// PASSO O NOME DO ARQUIVO PARA *argv
int main(int argc, char *argv[]) {
  List *list;
  int opcao;
  char arquivo[] = "entrada_30.txt";

  lines = contar_linhas(arquivo); // QUANTIDADE DE CIDADES

  int menorCaminho[lines];

  /*CRIA UM ARRAY DE LISTA*/
  list = list_new_vector(lines); // CRIO O ARRYLIST

  read_file(list, arquivo, lines); // LER ARQUIVO

  do {
    opcao = menu();
    switch (opcao) {
    case 1:
      printList(list);
      break;
    case 2:
      printListaCidades();
      break;
    case 3:
      dijikstra(list);
      break;
    }

  } while (opcao != 0);

  /*DESALOCO TODO ARRAY E SEUS ALEMENTOS*/
  list_clear_vector(list, lines);
  return 0;
}

/*------------------------------------------------------------*/
int menu() {
  int op;
  printf("\n-----OPCOES-----\n");
  printf("0 - Sair\n");
  printf("1 - Printar Grafo\n");
  printf("2 - Printar Cidades\n");
  printf("3 - Buscar melhor rota\n");

  do {
    printf("\nOpcao: ");
    scanf("%d", &op);
  } while (op < 0 || op > 3);

  return op;
}

/*------------------------------------------------------------*/
void escolherCidadeInicial(List *list, int *menorCaminho) {
  int opcao;

  printf("---Escolha a cidade inicial---\n");
  printListaCidades();
  printf("Opcao: ");
  scanf("%d", &opcao);

  menorCaminho[0] = opcao;
}

/*------------------------------------------------------------*/
long int contar_linhas(char *file_name) {
  FILE *fl = fopen(file_name, "r"); // ABRIR ARQUIVO PARA LEITURA
  int i;

  fscanf(fl, "%d", &i);

  fclose(fl);
  return i; // RETORNA A QUANTIDADE DE ALUNOS
}

/*------------------------------------------------------------*/
void get_file_element(List *l, FILE *fl, int n, int origem) {
  int destino;
  float distancia;

  for (destino = 0; destino < n; destino++) {

    fscanf(fl, "%f;", &distancia);

    // ADICIONANDO A DISTANCIA DAS CIDADES ADJACENTES
    if (distancia != 0)
      list_add(&l[origem], destino, distancia);
  }
}

/*------------------------------------------------------------*/
void read_file(List *l, char *file_name,
               long int line) { // Lista e o NOME do arquivo

  FILE *fl = fopen(file_name, "r");
  int i = 0, qtCidades;
  if (!fl) {
    printf("ERRO ao abrir o Arquivo!\n");
    exit(1);
  }

  fscanf(fl, "%d", &lines);

  while (!feof(fl)) {
    get_file_element(l, fl, qtCidades, i);
    i++;
  }

  fclose(fl);

  printf("Leitura de arquivo concluida\n");
}

/*------------------------------------------------------------*/
int **initVetor() {
  int i, e;
  int **vetor;

  vetor = (int **)malloc(lines * sizeof(int *));
  for (i = 0; i < lines; i++) {
    vetor[i] = (int *)malloc(lines * sizeof(int));
  }

  for (i = 0; i < lines; i++) {
    for (e = 0; e < lines; e++) {
      vetor[i][e] = 0;
    }
  }

  return vetor;
}

/*------------------------------------------------------------*/
void listForVetor(List *list, int **vetor) {
  int i;

  for (i = 0; i < lines; i++) {
    Node *no = get_first_element(&list[i]);
    while (!node_empty(no)) {
      vetor[i][get_id(no) - 1] = get_distancia(no);
      no = node_next(no);
    }
  }
}

/*------------------------------------------------------------*/
void freeVetor(int **vetor) {
  int i;

  for (i = 0; i < lines; i++) {
    free(vetor[i]);
  }
  free(vetor);
}

/*------------------------------------------------------------*/
void list_print(List *l) {
  Node *n = get_first_element(l);
  while (!node_empty(n)) { // PERCORRE TODOS OS ELEMENTOS DA LISTA
    printf("[%d, %f]\n", get_id(n), get_distancia(n));
    n = node_next(n);
  } // EXIBE O INDICE DO ARRAY
}

/*------------------------------------------------------------*/
void printList(List *list) {
  int i; // CONTADOR

  printf("\n\n==========LISTA=============\n");
  for (i = 0; i < lines; i++) { // ANDO PELA TABELA
    printf("(%d)\n", i);
    list_print(&list[i]); // EXIBE A LISTA DO INDICE i
  }
}

/*------------------------------------------------------------*/
void printListaCidades() {
  int i;
  for (i = 0; i < lines; i++) {
    printf("%d - ", i);
    printCidade(i);
    printf("\n");
  }
}

/*------------------------------------------------------------*/
void initEstimativas(float *vet) { // ASSINATURA
  int i;
  for (i = 0; i < lines; i++) {
    vet[i] = 9999;
  }
}

/*------------------------------------------------------------*/
void printInfCidade(int n) {
  printf("%d - ", n);
  printCidade(n);
}

/*------------------------------------------------------------*/
void initPrecedentes(int *vet) { // ASSINATURA
  int i;
  for (i = 0; i < lines; i++) {
    vet[i] = -1;
  }
}
/*------------------------------------------------------------*/
void initFinalizado(int *vet) { // ASSINATURA
  int i;
  for (i = 0; i < lines; i++) {
    vet[i] = 0;
  }
}

/*------------------------------------------------------------*/
int getOrigem() {
  int cit;
  do {
    printf("\nLocal de ORIGEM: ");
    scanf("%d", &cit);
  } while (cit < 0 || cit > 29);
  return cit;
}

/*------------------------------------------------------------*/
int getDestino() {
  int cit;
  do {
    printf("\nLocal de DESTINO: ");
    scanf("%d", &cit);
  } while (cit < 0 || cit > 29);
  return cit;
}

/*------------------------------------------------------------*/
int encontrarMenorVertice(List *list, float *estimativa, int *finalizado) {
  Node *no = get_first_element(list);
  int menorVert, menor = 9999;

  while (!node_empty(no)) {
    int idAdj = get_id(no);
    if (finalizado[idAdj] == 0) {
      if (estimativa[idAdj] < menor) {
        menorVert = idAdj;
        menor = estimativa[idAdj];
      }
    }
    no = node_next(no);
  }
  return menorVert;
}

/*------------------------------------------------------------*/
void geraCaminho(float *estimativa, int *precedente, int origem, int destino) {
  int atual = destino;

  printf("\n\n\t\t======| RESULTADO FINAL |======\n\n");
  printf("\t\t(CAMINHO ENCONTRADO)\n\n");

  printf("(%.2f  kms)\n", estimativa[atual]);
  while (atual != origem) {
    printInfCidade(atual);
    printf("\n");
    atual = precedente[atual];
  }
  printInfCidade(origem);
  printf("\n");
}

/*------------------------------------------------------------*/
void buscarMenorCaminho(List *list, float *estimativas, int *precedentes,
                        int *finalizado, int origem, int destino) {
  int ultimo = origem;
  int menorVert;
  Node *no;

  while (ultimo != destino) {
    no = get_first_element(&list[ultimo]);

    while (!node_empty(no)) {
      int citAdj = get_id(no);

      if (finalizado[citAdj] == 0) {
        float caminho = get_distancia(no) + estimativas[ultimo];

        if (caminho < estimativas[citAdj]) {
          estimativas[citAdj] = caminho;
          precedentes[citAdj] = ultimo;
        }
      }
      no = node_next(no);
    }
    menorVert = encontrarMenorVertice(&list[ultimo], estimativas, finalizado);

    ultimo = menorVert;
    finalizado[ultimo] = 1;
  }
  geraCaminho(estimativas, precedentes, origem, destino);
}

/*------------------------------------------------------------*/
void dijikstra(List *list) {
  float estimativas[lines];
  int precedentes[lines], finalizado[lines];
  int origem, destino;

  origem = getOrigem();
  destino = getDestino();

  initEstimativas(estimativas);
  initPrecedentes(precedentes);
  initFinalizado(finalizado);

  estimativas[origem] = 0;
  precedentes[origem] = origem;
  finalizado[origem] = 1;

  buscarMenorCaminho(list, estimativas, precedentes, finalizado, origem,
                     destino);
}
