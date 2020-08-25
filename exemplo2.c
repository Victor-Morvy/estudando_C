#include <windows.h>

int main(){
	
	int i;
	
	for(i=0; i<100; i++){
		printf("%i\t", i);
		
		//esperar um tempo
		Sleep(1000);
		
	}
	
	getch();
}
