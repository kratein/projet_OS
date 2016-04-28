#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define valeur_min_du_tableau 1000

 

typedef struct intermediaire{
	pid_t pid;
	FILE* fichier_perso;
}intermediaire;

typedef struct esclave{
	
	////////////////////////////////////////////////
	FILE* intermediaire,fichier_perso;				//// danger
	////////////////////////////////////////////////
	
	pid_t pid;
	int depart; // il faut bien qu'ils commence qq part dans le fichier
	int nombre_de_ligne_a_faire; // soit 100 soit X tel que 0 < X < 100
}esclave;



int main(){
	 
	 intermediaire tableau[valeur_min_du_tableau];
	 // just pour pas avoir de bug
	 return 0;
}

