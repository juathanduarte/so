#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct processos{
    char nome[4];
    int tempo;
} Processo;

Processo processos[9];

typedef struct processadores {
    Processo processos[5];
} Processador;

Processador processadores[2];

int main(){
    loadTaks(processos, 9);

    shortestJobFirst(processos, 9);

    organizeProcessors(processos, processadores, 9);

    return 0;
}

void loadTaks(Processo processos[], int n){
    int i;

    FILE * arq = NULL;    

    if((arq = fopen("tarefas.txt", "r")) == NULL){
        printf("Não foi possível abrir o arquivo\n\n");
        exit(1);
    }

    printf("Lista não ordenada:\n");

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

    printf("\nLista ordenada:\n");
    for(i=0; i<n; i++){
        printf("%s %d\n", p[i].nome, p[i].tempo);
    }
}

void organizeProcessors(Processo processos[], Processador processadores[],int n){
    int nextProcessOne = 0;
    int nextProcessTwo = 0;
    int time = 0;

    FILE * arq = NULL;

    if((arq = fopen("resultado.txt", "w")) == NULL){
        printf("Não foi possível abrir o arquivo\n\n");
        exit(1);
    }

    printf("Lista não ordenada:\n");

    for (int i = 0; i < n; i++){
        if (i%2 == 0){
            processadores[0].processos[nextProcessOne] = processos[i];
            nextProcessOne++;
        } else {
            processadores[1].processos[nextProcessTwo] = processos[i];
            nextProcessTwo++;
        }
    }

    printf("\n\n");

    fprintf(arq, "Processador 1:\n");

    for (int i = 0; i < nextProcessOne; i++){
        fprintf(arq, "%s;%d;%d\n", processadores[0].processos[i].nome, time, time + processadores[0].processos[i].tempo);
        time += processadores[0].processos[i].tempo;
    }

    time = 0;

    fprintf(arq, "\nProcessador 2:\n");

    for (int i = 0; i < nextProcessTwo; i++){
        fprintf(arq, "%s;%d;%d\n", processadores[1].processos[i].nome, time, time + processadores[1].processos[i].tempo);
        time += processadores[1].processos[i].tempo;
    }
    
    fclose(arq);
}