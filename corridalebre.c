#define TAM_PISTA 20
#include <windows.h>
#include <semaphore.h>
#include <locale.h>

int podio[3]; //global, compartilhada entre as threads
int posicao = 0;

sem_t meu_semaforo;

//definir o pulo aleatório entre 1 e 3
//falta a lebre esperar a vez dela(pula e descansa)
//Juiz!! para ver quem ganhou. (controle externo)
//Quantidade de pulos para cada lebre

//função executado pelas 2 threads
DWORD WINAPI Lebre (LPVOID lpParam)
{
	setlocale(NULL, "");
	long int numeroLebre = (int) lpParam;
	int pulo = 0;
	int andou = 0;
	
	while(andou<TAM_PISTA){
		pulo = 1;
		andou += pulo;
		printf("Sou a lebre %d, Pulei: %d, já andei: %d.\n", numeroLebre, pulo, andou);
	}
	posicao++;
	printf("Sou a lebre: %i. Terminei a corrida. Posição: %i\n", numeroLebre, posicao);
		
	
}

int main(){
	
	sem_init(&meu_semaforo, 0, 1);
	
	DWORD dwThreadIdArray;
	HANDLE thLebre1, thLebre2, thLebre3, thLebre4, thLebre5;//declara threads
	
	//SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	
	//criação da thread 1
	/*
	hThread1 = (HANDLE) CreateThread(
		NULL,					//atributos de segurança padrao
		0,						//tamanho da pilha padrão
		Trabalho,				//nome da função da thread
		(int *) 1,				//argumento para  a função da thread
		CREATE_SUSPENDED,		//tipo da criação
		&dwThreadIdArray);		//retorno do id da thread
	*/
	
	//SetThreadPriority(GetCurrentProcess(), HIGH_PRIORITY_CLASS)
	
	
	//criação da thread 2
	sem_wait(&meu_semaforo);
	thLebre1 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 1, CREATE_SUSPENDED, &dwThreadIdArray);
	sem_post(&meu_semaforo);
	sem_wait(&meu_semaforo);
	thLebre2 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 2, CREATE_SUSPENDED, &dwThreadIdArray);
	sem_post(&meu_semaforo);
	sem_wait(&meu_semaforo);
	thLebre3 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 3, CREATE_SUSPENDED, &dwThreadIdArray);
	sem_post(&meu_semaforo);
	sem_wait(&meu_semaforo);
	thLebre4 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 4, CREATE_SUSPENDED, &dwThreadIdArray);
	sem_post(&meu_semaforo);
	sem_wait(&meu_semaforo);
	thLebre5 = (HANDLE) CreateThread(NULL, 0, Lebre, (int *) 5, CREATE_SUSPENDED, &dwThreadIdArray);
	sem_post(&meu_semaforo);
	
	/*
	SetThreadPriority(thLebre1, THREAD_PRIORITY_IDLE);
	SetThreadPriority(thLebre1, THREAD_PRIORITY_IDLE);
	SetThreadPriority(thLebre1, THREAD_PRIORITY_IDLE);
	SetThreadPriority(hThread2, THREAD_PRIORITY_IDLE);
	SetThreadPriority(hThread1, THREAD_PRIORITY_IDLE);
	*/
	
	pthread_join(thLebre1, NULL);
	pthread_join(thLebre2, NULL);
	pthread_join(thLebre3, NULL);
	pthread_join(thLebre4, NULL);
	pthread_join(thLebre5, NULL);
	
	sem_destroy(&meu_semaforo);
	
	ResumeThread(thLebre1);
	ResumeThread(thLebre2);
	ResumeThread(thLebre3);
	ResumeThread(thLebre4);
	ResumeThread(thLebre5);
	
	getch();
	
	
}
