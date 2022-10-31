// Implemente o algoritmo do Banqueiro
// – Pergunte ao usuário a quantidade de Processos e Recursos.
// – Gere aleatoriamente a quantidade total de cada recurso. Ex.: 0 a 9.
// – Gere aleatoriamente a quantidade necessária de cada recurso por
// processo. Ex.: de 0 a 100% de cada recurso.
// – Gere aleatoriamente a quantidade de recurso alocado inicialmente para
// cada processo. Ex.: 0 a 50%.
// – Espera-se como resultado, algo como:
// • Imprimir todos os dados gerados aleatoriamente e a sequência segura
// (ou uma informação que não é possível uma sequência segura)
// • Ex.: A sequência segura é: Processo1 -> Processo3 -> Processo4 ->
// Processo0 -> Processo2

#include <stdio.h>
#include <stdlib.h>

int main(){
    int processos = 0;
    int recursos = 0;

    printf("Digite a quantidade de processos: ");
    scanf("%d", &processos);

    printf("Digite a quantidade de recursos: ");
    scanf("%d", &recursos);

    printf("\n");

    int recursosAlocados[processos][recursos];

    printf("Recursos alocados: \n");
    for (int i=0; i < processos; i++){
        for (int j=0; j < recursos; j++){
            recursosAlocados[i][j] = rand() % 10;
            printf("%d ", recursosAlocados[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // int recursosAlocados[recursos];
    int recursosDisponiveis[recursos];
    int recursosExistentes[recursos];

    printf("Recursos existentes: \n");
    for (int i=0; i < recursos; i++){
        recursosExistentes[i] = rand() % 10; // Gere aleatoriamente a quantidade total de cada recurso. Ex.: 0 a 9.
        recursosDisponiveis[i] = recursosExistentes[i];
        printf("%d ", recursosExistentes[i]);
    }

    printf("\n\n");

    int recursosNecessarios[processos][recursos];

    printf("Recursos necessarios: \n");
    for (int i=0; i < processos; i++){
        for (int j=0; j < recursos; j++){
            recursosNecessarios[i][j] = rand() % (recursosExistentes[j]);
            printf("%d ", recursosNecessarios[i][j]);
        }
        printf("\n");
    }

    while ()
 
    // printf("Recursos disponiveis: \n");
    // for (int i=0; i < recursos; i++){
    //     printf("%d ", recursosDisponiveis[i]);
    // }

    // printf("\n");
    
}