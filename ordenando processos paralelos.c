#define TAM_PISTA 20
#define TAM_PULO 3
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <time.h>


int get_posicao_podium(){
	FILE* arq;
	
	char c, letra = '\n';
	int vezes;
	
	if((arq = fopen("podium.txt", "r")) == NULL){
		return 1;
	} else {
		while(fread (&c, sizeof(char), 1, arq)) {
            if(c == letra) {
                vezes++;
            }
        } 
	}
	
	fclose(arq);
	return vezes+1;
	
}

int main()
{	
	clock_t t0, tf;
   	double tempo_gasto;
   	
   	FILE* arquivo;

   	t0 = clock();

	HANDLE hMutex = CreateMutex(NULL, FALSE, "Lebre"); //criação do mutex
	int j, distPercorrido=0, posicao=0;
	int pulo=0, lebreId;
	
	while(distPercorrido<TAM_PISTA)
	{
			
		
		system("cls");
		srand(time(NULL)); // semeia para ser aleatório
		pulo = (rand() % TAM_PULO)+1; // sorteio entre 1 e 3
		lebreId = GetCurrentThreadId();
		
		printf("Sou a lebre %d. Ja percorri %d metros.\n", GetCurrentThreadId(), distPercorrido);
		//---------------------------------------
		// protocolo de entrada na região na seção crítica
		WaitForSingleObject(hMutex, INFINITE); 
		//---------------------------------------
		
		printf("Sou a lebre %d. E acabei de pular %d metros!\n", lebreId, pulo);
		for (j=0; j<1000000000;j++); //gasta tempo
		distPercorrido += pulo;
		
		
		//---------------------------------------
		//Protocolo de saída da seção crítica
		ReleaseMutex(hMutex); //fim da seção crítica
		//---------------------------------------
		
	}
	
	//-------------------------------
	//destruindo o MUTEX
	CloseHandle(hMutex);
	//-------------------------------
	
	tf = clock();
   	tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
   	
   	arquivo = fopen("podium.txt", "a");
   	fprintf(arquivo, "#%d: Lebre: %d finalizado em %lf s\n", get_posicao_podium(), lebreId, tempo_gasto);
   	fclose(arquivo);
   	printf("Tempo gasto: %lf s\n", tempo_gasto);
	
	system("pause");
	return 0;
	
}
