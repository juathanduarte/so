#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *Funcao(void *argumento){
    int a=0;
    
    printf ("Sou a thread %ld e pertenço ao processo %d (para o SO meu pid=%lu)\n",
    pthread_self(), getpid(), syscall(__NR_gettid));
    while(1) a = 1; // loop infinito
    printf ("\n\nEncerrando a thread\n");
    fflush(stdout);
}

int main(void){
    pthread_t id;
    pthread_create(&id, NULL, Funcao, NULL);
    sleep(5);
    return(0);
}