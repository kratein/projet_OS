#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#define SIZE_BUF 4

int main(int argc, char** argv)
{
	int i,pid,n;
	int tabPid[argc-2]; 
	char buf[SIZE_BUF];
	if(argc<3)
	{
		perror("Pas assez d'arguments");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<argc-2; i++){
		pid=fork();
		while(pid==-1)
			pid=fork();
		tabPid[i]=pid;
		if(tabPid[i]==0){
			//ouvrir le fichier et lire la 1er ligne
			//créer autant de thread que la valeur de la  1er ligne du fichier
			//on regarde la fonction voulu 
			//chaque thread l'exécute et remonte le résultat à leur processus
			//le processus effectue la fonction 
			//il remonte au processus maitre les résultats
			// le processus maitre fait la fonction
			//écrit le résultat dans un fichier text
			printf("pid: %d   ppid: %d\n", getpid(), getppid() );
		return 0;
		}
	}
	sleep(1);
	}
	exit(0);
}
