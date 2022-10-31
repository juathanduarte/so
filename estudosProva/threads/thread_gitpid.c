#include <stdio.h>
#include <unistd.h> // sleep
#include <pthread.h>

void *FuncaoThread(void *arg){
    printf("Sou a thread %u e pertenço ao processo %d\n", (unsigned int)pthread_self(), getpid());
    sleep(5);
    printf("Finalizando a thread\n");
    fflush(stdout);
}

int main(){
    pthread_t id;
    pthread_create(&id, NULL, FuncaoThread, NULL);
    sleep(1);
    pthread_exit(NULL);
}