/*
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
*/
#include <stdio.h>
int main ( void )
{
   static const char filename[] = "file.txt";
	FILE *file = fopen ( filename, "r" );
	if ( file != NULL )
	{
	char line [ 128 ]; /* or other suitable maximum line size */

	while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
	{
		printf("Ligne : %s", line); /* write the line */
		printf("int ecrit %d\n",atoi(line));
	}
		fclose ( file );
	}
	else
	{
		perror ( filename ); /* why didn't the file open? */
	}
	return 0;
}
