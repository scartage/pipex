#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
    int fd[2];

    if (pipe(fd) == -1){
        return (-1);
    }

    int pid1 = fork();
    if (pid1 < 0){
        return (2);
    }

    if (pid1 == 0){
        //child proccess 1 (ping);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        printf("hola test\n");
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }

    int pid2 = fork();
    if (pid2 < 0){
        return (3);
    }
    if (pid2 == 0){
        //child proccess 2 (grep)
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        printf("otro hijo\n");
        execlp("grep", "grep", "ttl", NULL);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return (0);
}