#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Financiamento {
  int id;
  float totalImovel;
  float especie;
  float taxas;
  float subsidio;
  int financiado;
  int momentoFinanciamento;
} financiamento;

typedef struct Banco {
  float especie;
  float taxas;
  float subsidio;
} banco;

banco instFinanceira;

int pessoasAtendidas;
int *sequenciaSegura;
int contadorSequenciaSegura = 0;

pthread_mutex_t mutexBanco = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexSequenciaSegura = PTHREAD_MUTEX_INITIALIZER;

void imprimeSequenciaSegura(int boolean, financiamento *pessoas);
void pedirFinanciamento(financiamento *pessoa);
void situacaoBanco(int boolean);
void devolverDinheiro(financiamento *pessoa);
void emprestimoBanco(financiamento *pessoa);
void verificaPessoasAtendidas();

int qtdPessoas;
int countWhile = 0;

int main() {
  system("clear || cls");

  srand(time(NULL));

  do {
    printf("Informe quantas pessoas querem financiamento: ");
    scanf("%d", &qtdPessoas);

    if (qtdPessoas <= 0) {
      printf("Informe um valor maior que 0 de pessoas.");
    }

  } while (qtdPessoas < 1);

  sequenciaSegura = (int *)malloc(qtdPessoas * sizeof(int));

  financiamento pessoas[qtdPessoas];

  instFinanceira.especie = (int)(500001 + rand() % 500000);
  instFinanceira.subsidio = (int)((100001 + rand() % 100000));
  instFinanceira.taxas = (int)(30001 + rand() % 30000);

  printf("\n\t----- Banco -----\n->Especie: R$ %.2f\n->Taxas: R$ %.2f\n->Subsidio: R$ %.2f\n", instFinanceira.especie, instFinanceira.taxas, instFinanceira.subsidio);

  pthread_t financiamentos[qtdPessoas];
  pthread_t deadlock;

  for (int i = 0; i < qtdPessoas; i++) {
    pessoas[i].id = i;
    pessoas[i].totalImovel = (float)(rand() % (int)instFinanceira.especie);
    int maximo = (int)(0.7 * pessoas[i].totalImovel);
    int minimo = (int)(0.4 * pessoas[i].totalImovel);
    pessoas[i].especie = (float)(rand() % (int)(maximo + 1 - minimo) + minimo);
    pessoas[i].taxas = (float)(rand() % (int)pessoas[i].totalImovel);

    int subsidio = rand() % 2;

    switch (subsidio) {
    case 0:
      pessoas[i].subsidio = (float)((int)pessoas[i].totalImovel * 0.05);
      break;
    case 1:
      pessoas[i].subsidio = (float)((int)pessoas[i].totalImovel * 0.1);
      break;
    case 2:
      pessoas[i].subsidio = (float)((int)pessoas[i].totalImovel * 0.2);
      break;
    }

    pessoas[i].financiado = 0;

    printf("\nPessoa %d -----\n->Total do imovel: R$ %.2f\n->Especie: R$ %.2f\n->Taxas: R$ %.2f\n->Subsidio: R$ %.2f\n", pessoas[i].id, pessoas[i].totalImovel, pessoas[i].especie, pessoas[i].taxas, pessoas[i].subsidio);
  }

  int boolean = 0;

  while ((contadorSequenciaSegura < qtdPessoas) && (countWhile < qtdPessoas)) {
    printf("\n--------------- INSTANTE %d ---------------\n", countWhile);
    for (int i = 0; i < qtdPessoas; i++) {
      int erro = pthread_create(&financiamentos[i], NULL, (void *)pedirFinanciamento, (void *)&pessoas[i]);
      if (erro) {
        printf("ERRO; pthread_create() devolveu o erro %d\n", erro);
        exit(-1);
      }
    }

    for (int i = 0; i < qtdPessoas; i++) {
      pthread_join(financiamentos[i], NULL);
    }

    countWhile++;
  }

  if (contadorSequenciaSegura < qtdPessoas) {
    printf("\n\n\t----- ESTADO INSEGURO -----\n");
    imprimeSequenciaSegura(boolean, pessoas);
    printf("->Pessoas que nao foram atendidas: \n");
    for (int i = 0; i < qtdPessoas; i++) {
      if (pessoas[i].financiado == 0) {
        printf("->Pessoa %d", pessoas[i].id);
      }
    }
    printf("\n");
  } else {
    boolean = 1;
    printf("\n\n\t----- ESTADO SEGURO -----\n");
    imprimeSequenciaSegura(boolean, pessoas);
    printf("\n");
  }

  pthread_mutex_destroy(&mutexBanco);
  pthread_mutex_destroy(&mutexSequenciaSegura);

  free(sequenciaSegura);
}

void imprimeSequenciaSegura(int boolean, financiamento *pessoas) {
  if (boolean == 1) {
    printf("\nSequencia segura:\n");
  } else {
    printf("\nSequencia insegura\n");
  }

  for (int i = 0; i < contadorSequenciaSegura; i++) {
    printf("Pessoa %d no momento %d", sequenciaSegura[i], pessoas[sequenciaSegura[i]].momentoFinanciamento);
    if (i != contadorSequenciaSegura - 1) {
      printf("-->");
    }
  }
  printf("\n");
}

void pedirFinanciamento(financiamento *pessoa) {
  if (pessoa->financiado == 0) {
    int boolean;

    printf("\nPessoa %d pedindo financiamento\n", pessoa->id);

    emprestimoBanco(pessoa);

    if (pessoa->financiado == 1) {
      boolean = 1;
      situacaoBanco(boolean);
      printf("\nPessoa %d esta pagando as parcelas...\n", pessoa->id);
      sleep(5 + rand() % 5);
      devolverDinheiro(pessoa);
      boolean = 0;
      situacaoBanco(boolean);

      pessoasAtendidas++;

      pthread_mutex_lock(&mutexSequenciaSegura);
      sequenciaSegura[contadorSequenciaSegura] = pessoa->id;
      contadorSequenciaSegura++;
      pthread_mutex_unlock(&mutexSequenciaSegura);
    }
  }
}

void situacaoBanco(int boolean) {
  if (boolean == 1) {
    pthread_mutex_lock(&mutexBanco);
    printf("\n\n\t----- Banco [Antes de pagar a parcela] -----\n->Especie: R$ %.2f\n->Taxas: R$ %.2f\n->Subsidio: R$ %.2f\n", instFinanceira.especie, instFinanceira.taxas, instFinanceira.subsidio);
    pthread_mutex_unlock(&mutexBanco);
  } else {
    pthread_mutex_lock(&mutexBanco);
    printf("\n\t----- Banco [Depois de pagar a parcela] -----\n->Especie: R$ %.2f\n->Taxas: R$ %.2f\n->Subsidio: R$ %.2f\n", instFinanceira.especie, instFinanceira.taxas, instFinanceira.subsidio);
    pthread_mutex_unlock(&mutexBanco);
  }
}

void devolverDinheiro(financiamento *pessoa) {
  pthread_mutex_lock(&mutexBanco);

  instFinanceira.especie += pessoa->especie;
  instFinanceira.taxas += pessoa->taxas;
  instFinanceira.subsidio += pessoa->subsidio;

  printf("\nPessoa %d devolveu o dinheiro com sucesso!", pessoa->id);

  pthread_mutex_unlock(&mutexBanco);
}

void emprestimoBanco(financiamento *pessoa) {
  pthread_mutex_lock(&mutexBanco);

  verificaPessoasAtendidas();

  float valorEmprestimoEspecie = pessoa->totalImovel - pessoa->especie - pessoa->subsidio;
  float valorTaxa = pessoa->totalImovel * 0.05;
  float valorEmprestimoTaxa = 0;

  int consegueLiberar = (instFinanceira.especie >= valorEmprestimoEspecie) && (instFinanceira.subsidio >= pessoa->subsidio) && (instFinanceira.taxas >= valorTaxa - pessoa->taxas);

  if (consegueLiberar) {
    instFinanceira.especie -= valorEmprestimoEspecie;
    instFinanceira.subsidio -= pessoa->subsidio;
    pessoa->especie += valorEmprestimoEspecie;

    if (valorTaxa > pessoa->taxas) {
      valorEmprestimoTaxa = valorTaxa - pessoa->taxas;
      instFinanceira.taxas -= valorEmprestimoTaxa;
      pessoa->taxas += valorEmprestimoTaxa;
    }

    pessoa->financiado = 1;
    pessoa->momentoFinanciamento = countWhile;

    printf("\nValor Total do Imovel: %.2f\nPessoa %d precisa de R$%.2f de especie e R$ %.2f de taxa", pessoa->totalImovel, pessoa->id, valorEmprestimoEspecie, valorEmprestimoTaxa);
    pthread_mutex_unlock(&mutexBanco);
  } else {
    printf("Nao foi possivel liberar o emprestimo para a pessoa %d\n", pessoa->id);
    pthread_mutex_unlock(&mutexBanco);
  }
}

void verificaPessoasAtendidas() {
  if (pessoasAtendidas >= 3) {
    printf("Banco atendeu 3 pessoas e recebeu um bônus de 50%% de subsidio!\n");
    instFinanceira.subsidio += instFinanceira.subsidio * 0.5;
    pessoasAtendidas = 0;
  }
}