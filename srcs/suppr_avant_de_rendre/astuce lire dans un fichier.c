int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
 
    fichier = fopen("test.txt", "r");
 
    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
    
    
    
    
    
		while (caractereActuel != EOF){
			while (caractereActuel != "\n"){
            caractereActuel = fgetc(fichier);
            
            printf("%c", caractereActuel); // On l'affiche
            
			}
        } 
    
   /* 
        do
        {
            caractereActuel = fgetc(fichier); // On lit le caractère
            printf("%c", caractereActuel); // On l'affiche
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
 */
 
 
        fclose(fichier);
    }
 
    return 0;
}
