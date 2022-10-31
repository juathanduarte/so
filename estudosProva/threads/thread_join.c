#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *FuncaoThread(void *arg){
    printf("Sou a thread %u e pertenço ao processo %d\n", pthread_self(), getpid());
    sleep(5);
}

int main(){
    pthread_t id;
    pthread_create(&id, NULL, FuncaoThread, NULL);
    pthread_join(id, NULL);
}