#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char** argv)
{
	if(argc<3)
	{
		perror("Pas assez d'arguments");
		return 1;
	}
	int tabPid[argc];
	int i;
	for (i = 0; i < argc-3; ++i)
		if ((tabPid[i] = fork()) <= 0)
			break;
printf("toto \n");
	exit(0);
}
