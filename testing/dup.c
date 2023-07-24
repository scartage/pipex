#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/* Documentation:
    https://reactive.so/post/42-a-comprehensive-guide-to-pipex*/

int main(void)
{
    int fd;
    char *args[3];

    args[0] = "ls";
    args[1] = "-l";
    args[2] = "NULL";
    fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
    if (access("example.txt", R_OK) != -1)
        printf("I have permission\n");
    else
        printf("nope\n");
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execve("/bin/ls", args, NULL);
    printf("this is going to be printed in example.txt\n");
    return (0);
}