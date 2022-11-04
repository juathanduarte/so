#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct Financiamento {
  int id;
  float totalImovel;
  float especie;
  float taxas;
  float subsidio;
  int financiado;
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

void pedirFinanciamento();
void situacaoBanco();
void devolverDinheiro(financiamento *pessoa);
void emprestimoBanco(financiamento *pessoa);
void verificaPessoasAtendidas();

int main() {
  int qtdPessoas;
  srand(time(NULL));

  do {
    printf("Informe quantas pessoas querem financiamento: ");
    scanf("%d", &qtdPessoas);
  } while (qtdPessoas < 1);

  instFinanceira.especie = (int)(500001 + rand() % 500000);
  instFinanceira.subsidio = (int)((100001 + rand() % 100000));
  instFinanceira.taxas = (int)(30001 + rand() % 30000);

  printf("\nBanco -----\n-> Especie: R$ %.2f\n->Taxas: R$ %.2f\n->Subsidio: R$ %.2f\n", instFinanceira.especie, instFinanceira.taxas, instFinanceira.subsidio);

  financiamento pessoas[qtdPessoas];
  pthread_t financiamentos[qtdPessoas];

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

    printf("\nPessoa %d -----\n-> Total do imovel: R$ %.2f\n->Especie: R$ %.2f\n->Taxas: R$ %.2f\n->Subsidio: R$ %.2f\n", pessoas[i].id, pessoas[i].totalImovel, pessoas[i].especie, pessoas[i].taxas, pessoas[i].subsidio);
  }

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

  imprimeSequenciaSegura();
}

void imprimeSequenciaSegura() {
  printf("\nSequencia segura:\n");
  for (int i = 0; i < contadorSequenciaSegura; i++) {
    printf("Pessoa %d", sequenciaSegura[i]);
    if (i != contadorSequenciaSegura - 1) {
      printf("-->");
    }
  }
  printf("\n");
}

void pedirFinanciamento() {
  emprestimoBanco(&pessoas[i]);
  situacaoBanco();
  printf("\nPessoa %d esta pagando as parcelas...\n", pessoas[i].id);
  sleep(5 + rand() % 5);
  devolverDinheiro(&pessoas[i]);
  situacaoBanco();
  pessoasAtendidas++;
  sequenciaSegura[contadorSequenciaSegura] = pessoas[i].id;
  contadorSequenciaSegura++;
}

void situacaoBanco() {
  printf("\nBanco -----\n-> Especie: R$ %.2f\n->Taxas: R$ %.2f\n->Subsidio: R$ %.2f\n", instFinanceira.especie, instFinanceira.taxas, instFinanceira.subsidio);
}

void devolverDinheiro(financiamento *pessoa) {
  pthread_mutex_lock(&mutexBanco);
  instFinanceira.especie += pessoa->especie;
  instFinanceira.taxas += pessoa->taxas;
  instFinanceira.subsidio += pessoa->subsidio;
  pthread_mutex_unlock(&mutexBanco);
  pessoa->financiado = 1;
  printf("Pessoa %d devolveu o dinheiro com sucesso!\n", pessoa->id);
}

void emprestimoBanco(financiamento *pessoa) {
  verificaPessoasAtendidas();
  float valorEmprestimoEspecie = pessoa->totalImovel - pessoa->especie - pessoa->subsidio;
  float valorTaxa = pessoa->totalImovel * 0.05;
  float valorEmprestimoTaxa = 0;
  int consegueLiberar = (instFinanceira.especie >= valorEmprestimoEspecie) && (instFinanceira.subsidio >= pessoa->subsidio) && (instFinanceira.taxas >= valorTaxa - pessoa->taxas);

  if (consegueLiberar) {
    pthread_mutex_lock(&mutexBanco);
    instFinanceira.especie -= valorEmprestimoEspecie;
    instFinanceira.subsidio -= pessoa->subsidio;
    pessoa->especie += valorEmprestimoEspecie;
    if (valorTaxa > pessoa->taxas) {
      valorEmprestimoTaxa = valorTaxa - pessoa->taxas;
      instFinanceira.taxas -= valorEmprestimoTaxa;
      pessoa->taxas += valorEmprestimoTaxa;
    }
    pthread_mutex_unlock(&mutexBanco);

    printf("\nValor Total do Imovel: %.2f\nPessoa %d precisa de R$%.2f de especie\ne R$ %.2f de taxa", pessoa->totalImovel, pessoa->id, valorEmprestimoEspecie, valorEmprestimoTaxa);
  } else {
    printf("Nao foi possivel liberar o emprestimo para a pessoa %d", pessoa->id);
  }
}

void verificaPessoasAtendidas() {
  if (pessoasAtendidas >= 5) {
    printf("Banco atendeu 5 pessoas e recebeu um bônus de 50%% de subsidio");
    pthread_mutex_lock(&mutexBanco);
    instFinanceira.subsidio += instFinanceira.subsidio * 0.5;
    pthread_mutex_unlock(&mutexBanco);
    pessoasAtendidas = 0;
  }
}