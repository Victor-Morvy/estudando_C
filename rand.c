#include <stdio.h>
#include <time.h>

int main(){
	
	int i;
	int pulo;
	
	// semear o in�cio dos meus n�meros aleat�rios
	srand(time(NULL));
	
	for(i=0; i<10; i++){
		
		// de 0 at� MAX_RAND
		//printf("%i ", rand() % 100); //o resto da divis�o de 100 resulta um valor m�ximo de 100
		//sorteia o numero entre 1 e 3
		pulo = (rand() % 3)+1;
		printf("%i ", pulo);
	}
	getch();	
}

