#include "command.h"
#include "arguments.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include "file_handler.h"


static void print_char_array(char **array) {
    int i = 0;
    while (array[i] != NULL) {
        printf("[%d]%s\n",i, array[i]);
        i++;
    }
}

bool is_heredoc(char **av)
{
    return (ft_strncmp(av[1], "here_doc", 8) == 0);
}

void  close_pipes(int pipe[2])
{
    if (close(pipe[0] == -1))
        perror("closing the read end of the pipe");
    if (close(pipe[1] == -1))
        perror("closing the write end of the pipe");
}

/*ejecucion del primer comando*/
void  do_exec_call(char *com, char **envp)
{
    char **arguments;
    char *command_path;

    arguments = get_argument_array(com);
    print_char_array(arguments);
    if (arguments == NULL || arguments[0] == NULL)
        perror("command parsing problem");
    command_path = get_path(arguments[0], envp);
    printf("path: %s\n", command_path);
    if (execve(command_path, arguments, envp) == -1)
        perror("Problem executing command");
}

/*ejecucion del segundo comando*/
void exec_last_command(int ac, char **av, int fd[2], char **envp)
{
    int child;
    int status;
    char *com;
    
    com = av[ac - 2];
    printf("%s\n", com);
    child = fork();
    if (child == -1)
        perror("forking 2 command");
    if (child == 0)
    {
        printf("%s\n", av[ac - 1]); //mostramos el commando(?)
        set_outfile_fd(av[ac - 1], fd, is_heredoc(av));
        do_exec_call(com, envp);
    }
    close_pipes(fd);
    if (waitpid(child, &status, 0) == -1)
        perror("waiting for the last thread");
    while (wait(NULL) != -1)
        ;
    if (WIFEXITED(status))
        exit(WEXITSTATUS(status));
}