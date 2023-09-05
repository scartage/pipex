#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "file_handler.h"
#include "command.h"
#include "../inc/pipex.h"

void exec_first_command(char **av, int fd[2], char **envp)
{
    (void)fd;
    int pid_child;
    int file_fd;
    char *command;

    // guardamos el comando, av[1] es archivo de entrada 
    command = av[2];
    pid_child = fork();
    if (pid_child == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid_child == 0){
        //revisamos los permisos y de ahi sacamos el PID del input
        file_fd = check_read_perm(av[1]);
        /*en este punto ya esta modificada la entrada y salida del proceso hijo*/
        set_infile_fds(file_fd, fd);
        do_exec_call(command, envp);
    }
}

/*  fd[0]: es el descriptor de archivo para el extremo de lectura del pipe.
    fd[1]: es el descriptor de archivo para el extremo de escritura del pipe.*/

int main(int ac, char **av, char **envp)
{
    int fd[2];
    
    if (ac < 5)
    {
        ft_printf("numero de argumentos incorrecto %d\n", ac);
        printf("uso: ./pipex infile cmd1 cmd2 outfile\n");
        return (-1);
    }
    if (pipe(fd) == -1)
    {
        perror("Error en pipe");
        exit(EXIT_FAILURE);
    }
    exec_first_command(av, fd, envp);
    exec_last_command(ac, av, fd, envp);
    wait(NULL);
}