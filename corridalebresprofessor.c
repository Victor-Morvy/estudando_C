#define TAM_PISTA 2000
#define MAX_PULO 300
#include <windows.h>
#include <locale.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int podio[5];

int posicao=0;

sem_t sem1;

//sem_t meu_semaforo;

// Definir o pulo aleatório entre 1 e 3
// Falta a lebre esperar a vez dela (pula e descansa)
// Juiz!! Para ver quem ganhou.



DWORD WINAPI Lebre( LPVOID lpParam ) 
{ 	
	
	Sleep(30);
	
	srand(time(NULL));
	long int numeroLebre = (int)lpParam;  // parâmetro passado
	int pulo;
	
	int andou = 0;
	
	while(andou<TAM_PISTA)
	{
		//esperar a vez dela com semáforo
		sem_wait(&sem1);
		
		
		
		int pulo = rand() % MAX_PULO + 1;
		
		andou = andou + pulo;
		printf("Sou a lebre %i. Pulei: %i. Já andei: %i centímetros.\n", numeroLebre, pulo, andou);	
		
		sem_post(&sem1);
	}
	//colocar lebre no podio
	podio[posicao++] = numeroLebre;
	
	//printf("Sou a lebre %i. Terminei a corrida. Posição: %i\n", numeroLebre,posicao);
}

DWORD WINAPI Juiz( LPVOID lpParam ) 
{ 	
	//espera a corrida terminar
	
	//printf("Pthread juiz rodando 1\n");
	
	while(posicao!=5);
	printf("Juiz rodando analizando\n");
	//printf("Pthread juiz rodando 2\n");
	
	
	//depois que terminar, mostra o pódio
	
	int i;
	for(i=0; i<5; i++){
		printf("%io. lugar: %i\n", i+1, podio[i]);
	}
	
	
	
	
	
}

int main()
{
	
	
	setlocale(NULL,"");
	
	
	DWORD dwThreadIdArray;
	HANDLE  thLebre1, thLebre2, thLebre3, thLebre4, thLebre5, thJuiz;
	
	sem_init(&sem1, 0, 1);
	
	//sem_wait(&meu_semaforo);
	thLebre1 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 1, CREATE_SUSPENDED, &dwThreadIdArray);
	thLebre2 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 2, CREATE_SUSPENDED, &dwThreadIdArray);
	thLebre3 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 3, CREATE_SUSPENDED, &dwThreadIdArray);
	thLebre4 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 4, CREATE_SUSPENDED, &dwThreadIdArray);
	thLebre5 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 5, CREATE_SUSPENDED, &dwThreadIdArray);
	thJuiz = (HANDLE) CreateThread(NULL, 0, Juiz, (int *) 0, CREATE_SUSPENDED, &dwThreadIdArray);
	//SetThreadPriority(juiz, HIGH_PRIORITY_CLASS);
	
	//coloca os objetos no semáforo
	pthread_join(thLebre1, NULL);
	pthread_join(thLebre2, NULL);
	pthread_join(thLebre3, NULL);
	pthread_join(thLebre4, NULL);
	pthread_join(thLebre5, NULL);
	//pthread_join(thJuiz, NULL);
	
	// coloca as threads em execução
	ResumeThread(thLebre1);    
	ResumeThread(thLebre2);   
	ResumeThread(thLebre3);  
	ResumeThread(thLebre4);  
	ResumeThread(thLebre5);  
	ResumeThread(thJuiz);
	
	printf("Pressione qualquer tecla para terminar....\n");

	getch();
}

		
