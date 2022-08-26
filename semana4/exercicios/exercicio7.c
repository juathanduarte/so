#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MONOTHREAD 1
#define TWO_THREADS 2
#define FOUR_THREADS 4

int main(){
    int i, j, k;
    int **matriz;
    int num_threads;
    clock_t start, end;
    double cpu_time_used;
    pthread_t threads[FOUR_THREADS];
    int rc;
    long t;
    printf("Digite o número de threads: ");
    scanf("%d", &num_threads);
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &k);
    matriz = (int **)malloc(k*sizeof(int *));

    for(i=0; i<k; i++){
        matriz[i] = (int *)malloc(k*sizeof(int));
    }

    for(i=0; i<k; i++){
        for(j=0; j<k; j++){
            matriz[i][j] = rand()%100;
        }
    }

    if(num_threads == MONOTHREAD){
        start = clock();
        for(i=0; i<k; i++){
            for(j=0; j<k; j++){
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %f\n", cpu_time_used);
    }

    if(num_threads == TWO_THREADS){
        start = clock();
        for(i=0; i<k; i++){
            for(j=0; j<k; j++){
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %f\n", cpu_time_used);
    }
    
    if(num_threads == FOUR_THREADS){
        start = clock();
        for(i=0; i<k; i++){
            for(j=0; j<k; j++){
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %f\n", cpu_time_used);
    }
}
