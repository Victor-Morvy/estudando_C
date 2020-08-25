#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 3

int cont1 = 0;
int cont2 = 0;
sem_t t1;


struct WorkUnit
{
	int temp;

};



void *tratador1 (void *param) {
	
	int valor; 
    sem_getvalue (&t1, &valor); 
	
	if(valor == 0){

		cont1++;
		
		if(cont1 == 10){
			printf("Tratador 1 utilizado \n\n");
			cont1 = 0;
		}
	sem_post(&t1);
	}
	pthread_exit(NULL);
}

void *tratador2 (void *param) {
	
	int valor2; 
    sem_getvalue (&t1, &valor2);
	
	if(valor2 == 2){
		
		cont2++;
		
		if(cont2 == 10){
			printf("Tratador 2 utilizado \n\n");
			cont2 = 0;
		}
	
	sem_wait(&t1);
	}
	pthread_exit(NULL);
}

void *observador (void *param) {
	
	struct WorkUnit *wu = param;

	int temp = wu->temp;
	
	
	
	printf("Valor recebido \n\n");

	if(temp <= 40) { // condicao para decrementar o semaforo
		sem_wait(&t1);
		
	}else if(temp >= 50) {  // condicao para incrementar o semaforo
		sem_post(&t1);
		
	}
	pthread_exit(NULL);
}

int main (){
	
	int terror;
	int n;
	int t;
	void *(*functions[NUM_THREADS])(void *) = {tratador2, tratador1, observador};
	int valor[0];
	pthread_t tids [NUM_THREADS];
	
		
	sem_init (&t1, 0, 1); //iniciando o semaforo
		
	while (1) {
		
		
		printf("Digite o valor: ");
		scanf("%d", valor);
		
		
		for (n=0; n<NUM_THREADS; n++) {
			terror = pthread_create(&tids[n],NULL, functions[n], valor);
			
			if (terror) {
				errno = terror;
				perror("Falha na criação da thread");
				exit(EXIT_FAILURE);
			}
		}
		
		
		for (t = 0; t < NUM_THREADS; t++) {
			terror = pthread_join(tids[t], NULL);
			if (terror)
			{
				errno = terror;
				perror("Erro no Join!");
				exit(EXIT_FAILURE);
			}
		}
	}
		pthread_exit(NULL);
}



