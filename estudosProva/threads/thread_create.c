#include <stdio.h>
#include <unistd.h> // sleep
#include <pthread.h>

void *FuncaoThread(void *arg){
    printf("[Thread] Olá mundo!\n");
    fflush(stdout);
}

int main(){
    pthread_t id;
    pthread_create(&id, NULL, FuncaoThread, NULL);
    printf("[Main] Olá mundo!\n");
    pthread_exit(NULL);
}