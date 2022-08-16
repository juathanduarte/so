#include <stdio.h>
#include <string.h>

#define COUNTER_LETTERS_IN_NAME 5
#define QNT_PROCESSES 45

typedef struct processos {
    char name[COUNTER_LETTERS_IN_NAME];
    int time;
} Processo;

Processo processos[QNT_PROCESSES];

typedef struct processadores {
    Processo processos[QNT_PROCESSES]
} Processador;

void loadTaks(Processo processos[], int n, char fileName[]);
void biggestJobFirst(Processo *p, int n);

int main(int argc, char *argv[]){
    char fileName[12];
    stpcpy(fileName, argv[1]);

    int qntProcessors = atoi(argv[2]);

    Processador processadores[qntProcessors];

    loadTasks(processos, QNT_PROCESSES, fileName);
    biggestJobFirst(processos, QNT_PROCESSES);
    organizeProcesses(qntProcessors, processadores);

    return 0;
}

void loadTasks(Processo processos[], int n, char fileName[]){
    int i;

    FILE * arq = NULL;    

    if((arq = fopen(fileName, "r")) == NULL){
        printf("Não foi possível abrir o arquivo\n\n");
        exit(1);
    }

    printf("Lista não ordenada:\n");

    for(i=0; i<n; i++){
        fscanf(arq, "%s", &processos[i].name);
        fscanf(arq, "%d", &processos[i].time);

        printf("%s %d\n", processos[i].name, processos[i].time);
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

    printf("\nLista ordenada:\n");
    for(i=0; i<n; i++){
        printf("%s %d\n", p[i].name, p[i].time);
    }
}

void organizeProcesses(int qntProcessors, Processador processadores[]){
    char nextProcess[qntProcessors];
    char minTime[qntProcessors];

    for (int i = 0; i < qntProcessors; i++){
        minTime[i] = 0;
    }

    FILE * arq = NULL;

    if((arq = fopen("resultado.txt", "w")) == NULL){
        printf("Não foi possível abrir o arquivo\n\n");
        exit(1);
    }

    for(int i = 0; i<= qntProcessors; i++){
        for(int j = 0; j<= QNT_PROCESSES;j++){
            if((minTime[i] == 0) && (i <= 5)){
                processadores[j].processos[i] = processos[i];
            }
        }
        }
        if (minTime[i] == 0) {
            processadores[i].processos[i] = processos[i];
        }

        if (minTime[i + 1] < minTime[i]) {
            nextProcess[i] = processadores[i].processos[i].name;
            minTime[i] = processadores[i].processos[i].time;
        }
    }

        // processadores[j].processos[nextProcess[j]] = processos[i];
        // printf("\n\n%s;%d\n", processos[j].name, processos[j].time);
        // printf("%s----%d\n", processadores[j].processos[nextProcess[j]].name, processadores[j].processos[nextProcess[j]].time);

    // fprintf(arq, "Processador 1:\n");

    // for (int i = 0; i < nextProcessOne; i++){
    //     fprintf(arq, "%s;%d;%d\n", processadores[0].processos[i].nome, time, time + processadores[0].processos[i].tempo);
    //     time += processadores[0].processos[i].tempo;
    // }

    // time = 0;

    // fprintf(arq, "\nProcessador 2:\n");

    // for (int i = 0; i < nextProcessTwo; i++){
    //     fprintf(arq, "%s;%d;%d\n", processadores[1].processos[i].nome, time, time + processadores[1].processos[i].tempo);
    //     time += processadores[1].processos[i].tempo;
    // }
    
    // fclose(arq);
}