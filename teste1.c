#include <windows.h>
using namespace std;
#include <pthread.h>
pthread_t thread_1;
pthread_t thread_2;
// fun��o passada para a thread_1;
void* tarefa_1(void *p) {
//------------------------- REGI�O CR�TICA
for (char* s = "123456"; *s != '\0'; s++){
cout << *s;
}
//-----------------------------------------
}
// fun��o passada para a thread_2;
void* tarefa_2(void* p) {
//------------------------- REGI�O CR�TICA
for (char* s = "ABCDEF"; *s != '\0'; s++){
cout << *s;
}
//-----------------------------------------
}
int main()
{
cout << "Digite ENTER para iniciar as
threads..." << endl;
cin.get(); // aguarda um ENTER do usu�rio;
// inicia as duas threads, passando como
//par�metro a thread e a fun��o que cada uma
//deve executar;
pthread_create(&thread_1, NULL,
tarefa_1, NULL);
pthread_create(&thread_2, NULL,
tarefa_2, NULL);
// faz com que a thread principal espere a
'thread_1' e a 'thread_2' acabarem;
pthread_join(thread_1, NULL);
pthread_join(thread_2, NULL);
cin.get(); // aguarda um ENTER do usu�rio;
return 0;
}
