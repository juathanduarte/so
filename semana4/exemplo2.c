#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *Funcao(void *argumento){
    printf("Sou a thread %u e pertenço ao processo %u\n", (unsigned int)pthread_self(), getpid());
    sleep(30);
    printf("Finalizando thread\n");
    fflush(stdout);
}

int main(void){
    pthread_t id;
    pthread_create(&id, NULL, Funcao, NULL);
    pthread_exit(NULL);
}