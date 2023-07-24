#include <sys/types.h>
#include <sys/wait.h>
#include "../inc/pipex.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#define READ_END 0
#define WRITE_END 1

int main(int ac, char **av)
{
    int fd1[2], fd2[2];
    int status, pid;

    if (ac < 2)
    {
        ft_printf("numero de argumentos incorrecto\n");
        ft_printf("uso: ./pipex infile cmd1 cmd2 outfile\n");
        return (-1);
    }
    pipe(end);
    parent = fork();
    if (parent < 0){
        perror("Fork: ");
        return (-1);
    }
    if (!parent) // if fork() returns 0, we are in the child process
        child_process(av[1], av[2]);
    else
        parent_process(av[4], av[3]);
    return (0);
}