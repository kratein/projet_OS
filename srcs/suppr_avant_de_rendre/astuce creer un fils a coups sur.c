#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid_fils;

    do {
	pid_fils = fork();
    } while ((pid_fils == -1) && (errno == EAGAIN));

    return EXIT_SUCCESS;
}
