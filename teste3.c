#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/types.h>

 int g = 10;
void inc_by3() {
	g += 3;
}
void mul_by2() {
	g *= 2;
}

void main() {
	pid_t pid;
	int status;
	
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Unable to fork\n");
		return;
	} else if (pid == 0) { // Inside child process
		inc_by3();
		exit(0); // Finish child process
	} else { // Inside parent process
		mul_by2();
		waitpid(pid, &status, 0); // Waiting child finish
	}
	
	printf("%d\n", g);
}
