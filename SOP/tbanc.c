#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include "utils.h"

typedef struct conta{
    unsigned int numConta;
    double saldo;
    pthread_mutex_t lock;
}Conta;

typedef struct transferencia{
    unsigned int numOrigem;
    unsigned int numDestino;
    double quantidade;
    struct transferencia * proximo;
    struct transferencia * anterior;
}Transferencia;

typedef struct dex{
    int tamVetor;
    Conta* vetor;
}DescritorVetor;

typedef struct desc{
    int tamFila;
    Transferencia* inicio;
}DescritorFila;

void criaContas(char* arqcontas);
void criaFila(char* arqtrans);
void imprimeVetor();
void realizaTransferencias(void* arg);
unsigned int findConta(unsigned int conta);


pthread_mutex_t mutex;
sem_t semaphore;
int flagFim=0;

int transSucesso;
int transFeitas;

DescritorVetor* dVetor = NULL;
DescritorFila* dFila = NULL;

int main(int argc, char* argv[]){


    pthread_t* threads;

    int nthreads;
    int rc;
    long i;
    float taxa = 0;

    sscanf(argv[3],"%d",&nthreads);

    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaphore,0,0);
    criaContas(argv[1]);

    printf("Saldos iniciais:\n\n");
    imprimeVetor();

    threads = (pthread_t*) malloc( sizeof(pthread_t) * nthreads );

    for(i=0; i < nthreads; i++){
        if( (rc = pthread_create(&threads[i], NULL, (void*) realizaTransferencias,(void*) i)) != 0){
            printf("Thread %ld criada sem sucesso...\n", i);

        }
    }
    criaFila(argv[2]);

    for(i=0; i < nthreads; i++){
        rc = pthread_join(threads[i], NULL);
    }

    printf("\n-------------------------------------------\n");
    printf("Saldos finais:\n\n");
    imprimeVetor();
    
    free(threads);
    taxa = 100.0*( (float) transSucesso/transFeitas);
    printf("Foram lidas %d transacoes.\nE foram realizadas %d transacoes.\nUm indice de %.2lf%% de sucesso\n",transFeitas, transSucesso,taxa);

    return 0;
}

void criaContas(char* arqcontas){
    FILE *contas;

    int i;
    unsigned int conta;
    double saldo;


    contas = fopen (arqcontas, "r");

    dVetor = (DescritorVetor*) malloc( sizeof(DescritorVetor) );
    dVetor->tamVetor=0;
    dVetor->vetor=NULL;

    while( (fscanf(contas, "%d %lf\n", &conta, &saldo)) != EOF)
        dVetor->tamVetor++;



    dVetor->vetor = (Conta*) malloc(sizeof(Conta) * dVetor->tamVetor);


    rewind(contas);

    for(i=0; i< dVetor->tamVetor; i++){
        fscanf(contas, "%d %lf\n", &conta, &saldo);
        dVetor->vetor[i].numConta = conta;
        dVetor->vetor[i].saldo = saldo;
        pthread_mutex_init(&(dVetor->vetor[i].lock), NULL);
    }

    fclose(contas);

}

void criaFila(char* arqtrans){
    FILE* transacoes = NULL;
    Transferencia* builder = NULL;
    Transferencia* aux = NULL;

    unsigned int origem;
    unsigned int destino;
    double qtd;

    transacoes = fopen (arqtrans, "r");

    dFila = (DescritorFila*) malloc( sizeof(DescritorFila) );
    dFila->tamFila = 0;

    builder = (Transferencia*) malloc( sizeof(Transferencia) );
    
    builder->numDestino = 0;
    builder->numOrigem = 0;
    builder->quantidade = 0.0;
    builder->proximo = NULL;
    builder->anterior = NULL;    

    do{
        fscanf(transacoes, "%d %d %lf\n", &origem, &destino, &qtd);
    }while( (findConta(origem)) == -1 || (findConta(destino)) == -1);
    
    builder->numDestino = destino;
    builder->numOrigem = origem;
    builder->quantidade = qtd;


    pthread_mutex_lock(&mutex);

    dFila->inicio = builder;
    dFila->tamFila++;
    aux = dFila->inicio;
    builder = NULL;
    transFeitas++;

    sem_post(&semaphore);
    //printf("Botei uma requisicao na fila\n");
    rand_sleep(SLEEP_MAIN);

    pthread_mutex_unlock(&mutex);



    while( (fscanf(transacoes, "%d %d %lf\n", &origem, &destino, &qtd)) != EOF ){

        if(findConta(origem) == -1 || findConta(destino) == -1){
            transFeitas++;
            continue;
        }

        builder = (Transferencia*) malloc( sizeof(Transferencia) );
        builder->numDestino = destino;
        builder->numOrigem = origem;
        builder->quantidade = qtd;
        pthread_mutex_lock(&mutex);

        if(dFila->inicio == NULL){
            dFila->inicio = builder;
            aux = dFila->inicio;
            aux->anterior = NULL;
            aux->proximo = NULL;
        }

        else{
            aux->proximo = builder;
            aux->proximo->anterior = NULL;
            aux = aux->proximo;
        }

        dFila->tamFila++;
        builder = NULL;
        transFeitas++;

        sem_post(&semaphore);
        rand_sleep(SLEEP_MAIN);
        //printf("Botei uma requisicao na fila\n");

        pthread_mutex_unlock(&mutex);

    }

    flagFim = 1;
    sem_post(&semaphore);
    fclose(transacoes);
}

void realizaTransferencias(void* arg){
    Transferencia* aux;

    unsigned int origem = 0;
    unsigned int destino = 0;
    double qtd = 0.0;

    while(1){
        //printf("  %ld está na frente do semaforo\n",(long) arg);
        sem_wait(&semaphore);
        //printf("  %ld passou do semaforo\n",(long) arg);

        pthread_mutex_lock(&mutex);
        //printf("  %ld travou o mutex\n",(long) arg);

        if(dFila->inicio == NULL && flagFim != 0){
            pthread_mutex_unlock(&mutex);
            //printf("A thread %ld acabou!!\n",(long) arg);
            sem_post(&semaphore);
            break;
        }

        aux = dFila->inicio;
        dFila->inicio = aux->proximo;

        if(aux->proximo != NULL){
            aux->proximo->anterior = NULL;
            aux->proximo = NULL;
        }
        else
            dFila->inicio = NULL;

        //printf("  %ld destravou o mutex\n",(long) arg);
        pthread_mutex_unlock(&mutex);

        qtd = aux->quantidade;
        origem = aux->numOrigem;
        destino = aux->numDestino;
        /*
        printf("\n--------------------------------------------------\n");
        printf("Eu sou a thread %ld\n", (long) arg);
        printf("Conta: %d\n",origem);
        printf("\tSaldo: %.2lf ---> %.2lf\n",dVetor->vetor[findConta(origem)].saldo, dVetor->vetor[findConta(origem)].saldo - qtd);
        printf("Desti: %d\n",destino);
        printf("\tSaldo: %.2lf ---> %.2lf\n",dVetor->vetor[findConta(destino)].saldo, dVetor->vetor[findConta(destino)].saldo + qtd);
        printf("\n--------------------------------------------------\n");
        */

        pthread_mutex_lock(&(dVetor->vetor[findConta(origem)].lock));
        if(dVetor->vetor[findConta(origem)].saldo >= qtd){
            dVetor->vetor[findConta(origem)].saldo -= qtd;
            pthread_mutex_unlock(&(dVetor->vetor[findConta(origem)].lock));
            
            transSucesso++;
            
            pthread_mutex_lock(&(dVetor->vetor[findConta(destino)].lock));
            dVetor->vetor[findConta(destino)].saldo += qtd;
            pthread_mutex_unlock(&(dVetor->vetor[findConta(destino)].lock));

        }
        else{
            pthread_mutex_unlock(&(dVetor->vetor[findConta(origem)].lock));
        }
        rand_sleep(SLEEP_THREAD);

        aux = NULL;



    }

}

void imprimeVetor(){
    int i=0;

    for(i=0; i< dVetor->tamVetor; i++){
        printf("Conta %d\n", i+1);
        printf("\tnumConta = %d\n",dVetor->vetor[i].numConta);
        printf("\tsaldo = %.2lf\n",dVetor->vetor[i].saldo);
    }
    printf("\n");

}

unsigned int findConta(unsigned int conta){
    int i;
    unsigned int ret=0;

    for(i=0; i < dVetor->tamVetor; i++){
        if(conta == dVetor->vetor[i].numConta){
            ret = i;
            return ret;
        }
    }
    return -1;
}
