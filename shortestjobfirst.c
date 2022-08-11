#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct processos{
    char nome[4];
    int tempo;
} Processo;

Processo processos[9];

typedef struct processadores {
    int id;
    Processo processos;
} Processador;

Processador processadores[2];

int main(){
    loadTaks(processos, 9);

    printf("\n\n");

    shortestJobFirst(processos, 9);

    for(int i = 0; i < 9; i++){
        printf("%s %d\n", processos[i].nome, processos[i].tempo);
    }

    return 0;
}

void loadTaks(Processo processos[], int n){
    int i;

    FILE * arq = NULL;    

    if((arq = fopen("tarefas.txt", "r")) == NULL){
        printf("Não foi possível abrir o arquivo\n\n");
        exit(1);
    }

    for(i=0; i<n; i++){
        fscanf(arq, "%s", &processos[i].nome);
        fscanf(arq, "%d", &processos[i].tempo);
        printf("%s %d\n", processos[i].nome, processos[i].tempo);
    }

    fclose(arq);
    }

void shortestJobFirst(Processo *p, int n){
    int i, j;
    Processo aux;
    for (i = 0; i < n; i++){
        for (j = 0; j < n - 1; j++){
            if (p[j].tempo > p[j + 1].tempo){
                aux = p[j];
                p[j] = p[j + 1];
                p[j + 1] = aux;
            }
        }
    }
}

void organizeProcessors(Processador *p, int n){
    int counterOne = 0, counterTwo = 0;

    Processo aux;

    for (int i = 0; i < n; i++){
        if (p[i].processos.tempo < counterOne){
            aux = p[i];
            p[i] = p[counterOne];
            p[counterOne] = aux;
            counterOne++;
        }
        else if (p[i].processos.tempo < counterTwo){
            aux = p[i];
            p[i] = p[counterTwo];
            p[counterTwo] = aux;
            counterTwo++;
        } else {
            //TO-DO: ajeitar essa merda
        }
    }
}