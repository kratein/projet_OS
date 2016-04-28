#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#define SIZE_BUF 4



typedef struct intermediaire{
	pid_t pid;
	FILE* fichier_perso;
}intermediaire;

typedef struct esclave{
	pid_t pid;	
	FILE* fichier_perso_du_pere;			
	int depart; // il faut bien qu'ils commence qq part dans le fichier
	int nombre_de_ligne_a_faire; // soit 100 soit X tel que 0 < X < 100
}esclave;





















int main(int argc, char** argv)
{	intermediaire tab_inter[argc-2];
	int i,pid,n;
	char buf[SIZE_BUF];
	if(argc<3)// trop mignion le coeur
	{
		perror("Pas assez d'arguments");
		exit(EXIT_FAILURE);
	}
	
	
	for(i=0; i<argc-2; i++){
		tab_inter[i].pid = fork();
		while(tab_inter[i].pid==-1){
			tab_inter[i].pid=fork();}
		if(tab_inter[i].pid==0){
			//ouvrir le fichier et lire la 1er ligne
			//créer autant de thread que 1+ la valeur/100 de la  1er ligne du fichier
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
	
	exit(0);
}
