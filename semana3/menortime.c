#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COUNTER_LETTERS_IN_NAME 5
#define QNT_PROCESSES 45

typedef struct processos {
    char name[COUNTER_LETTERS_IN_NAME];
    int time;
} Processo;

Processo processos[QNT_PROCESSES];

typedef struct processadores {
    Processo processos[QNT_PROCESSES];
    int qnt_processos;
} Processador;

void loadTasks(Processo processos[], int n, char fileName[]);
void biggestJobFirst(Processo *p, int n);
void organizeProcesses(int qntProcessors, Processador processadores[]);
void printResult(Processador processadores[], int qntProcessors);

int main(int argc, char *argv[]){
    char fileName[12];
    stpcpy(fileName, argv[1]);

    int qntProcessors = atoi(argv[2]);

    Processador processadores[qntProcessors];

    for (int i = 0;i< qntProcessors; i++){
        processadores[i].qnt_processos = 0;
    }

    loadTasks(processos, QNT_PROCESSES, fileName);
    biggestJobFirst(processos, QNT_PROCESSES);
    organizeProcesses(qntProcessors, processadores);
    printResult(processadores, qntProcessors);

    return 0;
}

void loadTasks(Processo processos[], int n, char fileName[]){
    int i;

    FILE * arq = NULL;    

    if((arq = fopen(fileName, "r")) == NULL){
        printf("Não foi possível abrir o arquivo\n\n");
        exit(1);
    }

    for(i=0; i<n; i++){
        fscanf(arq, "%s", processos[i].name);
        fscanf(arq, "%d", &processos[i].time);
    }

    fclose(arq);
}

void biggestJobFirst(Processo *p, int n){
    int i, j;
    Processo aux;
    for (i = 0; i < n; i++){
        for (j = 0; j < n - 1; j++){
            if (p[j].time < p[j + 1].time){
                aux = p[j];
                p[j] = p[j + 1];
                p[j + 1] = aux;
            }
        }
    }
}

void organizeProcesses(int qntProcessors, Processador processadores[]){
    int processadorAtribuir = 0;

    for(int i =0; i < QNT_PROCESSES; i++){
        processadorAtribuir = i % qntProcessors;

        processadores[processadorAtribuir].processos[processadores[processadorAtribuir].qnt_processos] = processos[i];
        processadores[processadorAtribuir].qnt_processos++;
    }
}

void printResult(Processador processadores[], int qntProcessors){
    FILE * arq = NULL;

    int terminoProcessoAnterior = 0;

    if((arq = fopen("resultado.txt", "w")) == NULL){
        printf("Não foi possível abrir o arquivo\n\n");
        exit(1);
    }

    for(int i = 0; i < qntProcessors; i++){
        terminoProcessoAnterior = 0;
        fprintf(arq, "Processador_%d\n", i + 1);

        for(int j = 0; j < processadores[i].qnt_processos; j++){
            fprintf(arq, "%s;%d,%d\n", processadores[i].processos[j].name, terminoProcessoAnterior, terminoProcessoAnterior + processadores[i].processos[j].time);
            terminoProcessoAnterior += processadores[i].processos[j].time;
        }
    }
}