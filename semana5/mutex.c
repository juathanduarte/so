// Faça um programa que calcule a soma dos elementos de um vetor.

// Seu programa deverá receber dois parâmetros: o tamanho de um vetor (>=100) e um número de threads (>=2).

// O resultado do programa é o somatório dos elementos deste vetor.

// O programa deve criar um vetor do tamanho especificado, iniciá-lo com valores sintéticos (randomicos ou fixos, por exemplo, 1, 2, 3, ...) e reparti-lo entre as threads criadas, conforme o número de threads informado. Por exemplo, se o vetor tiver 100 posições, com 5 threads, então, cada thread irá somar 20 números do vetor.
// Orientação a ser seguida: o somatório deve ser realizado em uma variável compartilhada, sendo utilizado um mutex para coordenar o acesso a ela.

// mandar o vetor, e o que ela deve somar (de qual ponto ela deve iniciar até qual ponto somar)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct arguments {
    int *vetor;
    int pontoIncial;
    int pontoFinal;
};

struct arguments args;

int tamanhoVetor = 0;
int numThreads = 0;
int vetorDividido = 0;

void* thread_func(void *arg){
    struct arguments* args = (struct arguments *) arg;
    int* result = malloc(sizeof(int));

    *result = 0;

    for (int i= args -> pontoIncial; i <= args -> pontoFinal ; i++){
        *result += args->vetor[i];
    }

    return result;
}

int main(int argc, char *argv[]){
    tamanhoVetor = atoi(argv[1]);
    numThreads = atoi(argv[2]);

    vetorDividido = tamanhoVetor / numThreads;

    if (tamanhoVetor < 100 || numThreads < 2) {
        printf("O tamanho do vetor deve ser maior que 100 e o número de threads deve ser maior que 2!");

        return;
    }

    pthread_t threads[numThreads];

    for (int i = 0; i < numThreads; i++) {
        pthread_create(&(threads[i]), NULL, thread_func, NULL);
    }

    for (int i = 0; i < numThreads; i++){
        pthread_join(threads[i], NULL);
    }

    // for(int i= 0; i < tamanhoVetor; i++){
    //     printf("entrou");
    //     args.vetor[i] = 2;
    //     printf("[%d]: %d", i, args.vetor[i]);
    // }

    free(args.vetor);

    return 0;
}
