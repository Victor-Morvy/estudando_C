#include <windows.h>
using namespace std;
#include <pthread.h>
pthread_t thread_1;
pthread_t thread_2;
// função passada para a thread_1;
void* tarefa_1(void *p) {
//------------------------- REGIÃO CRÍTICA
for (char* s = "123456"; *s != '\0'; s++){
cout << *s;
}
//-----------------------------------------
}
// função passada para a thread_2;
void* tarefa_2(void* p) {
//------------------------- REGIÃO CRÍTICA
for (char* s = "ABCDEF"; *s != '\0'; s++){
cout << *s;
}
//-----------------------------------------
}
int main()
{
cout << "Digite ENTER para iniciar as
threads..." << endl;
cin.get(); // aguarda um ENTER do usuário;
// inicia as duas threads, passando como
//parâmetro a thread e a função que cada uma
//deve executar;
pthread_create(&thread_1, NULL,
tarefa_1, NULL);
pthread_create(&thread_2, NULL,
tarefa_2, NULL);
// faz com que a thread principal espere a
'thread_1' e a 'thread_2' acabarem;
pthread_join(thread_1, NULL);
pthread_join(thread_2, NULL);
cin.get(); // aguarda um ENTER do usuário;
return 0;
}
