#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    pid_t pid;
    char buffer[13];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(fd[0]); //close read end of the pipe
        write(fd[1], "hello parent!", 13);
        close(fd[1]); //close the write of the pipe
        sleep(3);
        exit(EXIT_SUCCESS);  
    }else{
        close(fd[1]); //close the write of the pipe
        read(fd[0], buffer, 13);
        close(fd[0]);
        wait(NULL);
        printf("Message from child: %s\n", buffer);
    }
    exit(EXIT_SUCCESS);
}
