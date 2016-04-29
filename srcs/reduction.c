#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>
float max(float valeurs[],int numeroLigne)
{
    int i;
    float max=valeurs[0];
    int taille = numeroLigne;
    for(i=0;i<taille;i++)
    {
        if(valeurs[i]>max)
        
            max=valeurs[i];
    }
    return max;
}
float min(float valeurs[],int numeroLigne)
{
    int i;
    float min=valeurs[0];
    int taille = numeroLigne;
    for(i=0;i<taille;i++)
    {
        if(valeurs[i]<min)
        
            min=valeurs[i];
    }
    return min;
}

float sum(float valeurs[],int numeroLigne)
{
    int i;
    float sum=0;
        int taille = numeroLigne;
    for(i=0;i<taille;i++)
    {
        sum+=valeurs[i];
    }
    return sum;
}

float odd(float valeurs[],int numeroLigne)
{
    int i;
    float odd=0;
    int taille = numeroLigne;
    for(i=0;i<taille;i++)
    {
        if(((int)valeurs[i]%2)==1)
            odd+=1;
    }
    return odd;
}

float avg(float valeurs[],int numeroLigne)
{
    int taille = numeroLigne;
    return sum(valeurs,taille)/taille;
}


char* read_line(int fd)
{
    if (fd < 0)
    {
            perror("impossible d’ouvrir le fichier");
    exit (EXIT_FAILURE);
    }
    int i=0;
    char *line = NULL;
    char courant;
    int res = read(fd,&courant,1);
    if (res == 1)
    {
        line=(char *)malloc(sizeof(char));
        while(courant!='\n' && res == 1)
        {
            line[i]=courant;
            i++;
            line = (char *)realloc(line,(1+i)*sizeof(char));
            res = read(fd,&courant,1);
        }
        line[i]='\0';
    }
    return line;
}
float affiche_resultat(int f, char** argv){
	
    char * retour=(char *)malloc(sizeof(char));
    float* valeur=(float *)malloc(sizeof(float));
    float resultat;
    int numeroLigne=0;

     while ((retour  = read_line(f)) != NULL){
		 //printf("je suis dans le while\n");
         valeur[numeroLigne]=atof(retour);
         //printf("Ligne %d : %f\n", numeroLigne, valeur[numeroLigne]);
         valeur= (float *)realloc(valeur,(4+numeroLigne)*sizeof(float));
         free(retour);
         numeroLigne++;    
     }
	if(strcmp(argv[1],"min") ==0)
        resultat=min(valeur,numeroLigne);
    else if(strcmp(argv[1],"max")==0)
        resultat=max(valeur,numeroLigne);
    else if(strcmp(argv[1],"avg")==0)
        resultat=avg(valeur,numeroLigne);
    else if(strcmp(argv[1],"sum")==0)
        resultat=sum(valeur,numeroLigne);
    else if(strcmp(argv[1],"odd")==0)
        resultat=odd(valeur,numeroLigne);	
	printf("resultat %f \n",resultat);
    return resultat;
}    

int main(int argc, char**argv){     
    
    
    if(argc < 3){
    perror("pas assez d’arguments");
    return EXIT_FAILURE;
    }


   if(strcmp(argv[1],"min") != 0 && strcmp(argv[1],"max") != 0 && strcmp(argv[1],"agv") != 0 && strcmp(argv[1],"sum") != 0 && strcmp(argv[1],"odd") != 0){
    perror("fonction non valide");
    exit (EXIT_FAILURE);
    }
    
    char * retour=(char *)malloc(sizeof(char));    
    float resultat;
    int numeroLigne=0;
    int ecriture;
    char* resul=(char *)malloc(sizeof(char)); 
    int fd,status,fd1;
   float *valeur= (float *)malloc(sizeof(float));
    char buffer[20];
    int i=0;
    pid_t pid=1;
    int file[2];
    char position;
	pipe(file);
	write(file[1],"2",sizeof(int));
	float resultatFils;


    while(i<argc-2 && pid >0)    {                        
        pid=fork();
        i++;
        if(pid==-1){
            perror("fork erreur");
            exit(EXIT_FAILURE);
        }
        if(pid==0)
        {
			read(file[0],&position,sizeof(int));			
			printf("j'ouvre le fichier %s %c\n",argv[atoi(&position)],position);                
			fd=open(argv[atoi(&position)],O_RDONLY);
			gcvt(atoi(&position)+1,1,buffer);			
			write(file[1],buffer,sizeof(int));     
			close(file[0]);
			close(file[1]);        
			resultatFils = affiche_resultat(fd,argv);
			//printf("mon resultat fils est %f \n",resultatFils);
			close(fd);			
			
			fd1=open("fifo.txt", O_WRONLY|O_APPEND|O_CREAT);
			
			if (fd1<0){
				perror("impossible d'ecrire");
				exit (EXIT_FAILURE);
			}	
			gcvt(resultatFils,10,resul);
			resul=strcat(resul,"\n");		
			write(fd1,resul,strlen(resul));
			close(fd1);			
			exit(EXIT_SUCCESS);	
		}
    } 
    for(i=0;i<argc-2;i++)
    {
        wait(&status);
    }
    fd=open("fifo.txt",O_RDONLY);
    while ((retour  = read_line(fd)) != NULL){
         valeur[numeroLigne]=atof(retour);
         //printf("Ligne %d : %f\n", numeroLigne, valeur[numeroLigne]);
         valeur= (float *)realloc(valeur,(4+numeroLigne)*sizeof(float));
         free(retour);
         numeroLigne++;    
     }
     close(fd);
     	if(strcmp(argv[1],"min") ==0)
        resultat=min(valeur,numeroLigne);
    else if(strcmp(argv[1],"max")==0)
        resultat=max(valeur,numeroLigne);
    else if(strcmp(argv[1],"avg")==0)
        resultat=avg(valeur,numeroLigne);
    else if(strcmp(argv[1],"sum")==0)
        resultat=sum(valeur,numeroLigne);
    else if(strcmp(argv[1],"odd")==0)
        resultat=odd(valeur,numeroLigne);
    remove("data/resultat.txt");
	fd=open("data/resultat.txt",O_WRONLY|O_CREAT,0666);
	gcvt(resultat,10,resul);
	ecriture=write(fd,resul,strlen(resul));
	printf("resultat général %f \n",resultat);
    if (ecriture<0){
		perror("impossible d'ecrire");
        exit (EXIT_FAILURE);
    }
    close(fd);
    remove("fifo.txt");
    free(resul);
    free(valeur);
    return 0;
}
