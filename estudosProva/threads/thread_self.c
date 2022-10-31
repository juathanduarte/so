#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *FuncaoThread(void *arg){
    int a = 0;

    printf("Sou a thread %u e pertenço ao processo %d (para o SO meu pid é %lu)\n", pthread_self(), getpid(), syscall(__NR_gettid));

    while(1) a = 1;

    printf("Finalizando a thread\n");
    fflush(stdout);
}

int main(){
    pthread_t id;
    pthread_create(&id, NULL, FuncaoThread, NULL);
    sleep(5);
    // pthread_exit(NULL);
}