#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "file_handler.h"
#include "command.h"

void exec_first_command(char **av, int fd[2], char **envp)
{
    int pid_child;
    int file_fd;
    char *command;

    command = av[2];
    printf("%s\n", command);
    pid_child = fork();
    if (pid_child == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid_child == 0){
        file_fd = check_read_perm(av[1]);
        set_infile_fds(file_fd, fd);
        do_exec_call(command, envp);
    }
}

int main(int ac, char **av, char **envp)
{
    int fd[2];

    if (ac < 2)
    {
        printf("numero de argumentos incorrecto\n");
        printf("uso: ./pipex infile cmd1 cmd2 outfile\n");
        return (-1);
    }
    if (pipe(fd) == -1)
    {
        perror("Error en pipe");
        exit(EXIT_FAILURE);
    }

    exec_first_command(av, fd, envp);
    wait(NULL);
}