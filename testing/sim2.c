#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    pid_t pid;

    //crear pipe
    if (pipe(fd) == -1){
        perror("pipe\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1){
        perror("fork");
        exit(EXIT_SUCCESS);
    }

    if (pid == 0){
        // child process

        //cerramos el extremo de lectura del pipe
        close(fd[0]);
        //redireccionamos la STDOUT al extremo de end write
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        //Ejecutamos ls -l
        char * argv[] = {"/bin/ls", "-l", NULL};
        if (execve(argv[0], argv, NULL) == -1){
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    
    int pid2 = fork();
    if (pid2 == -1){
        perror("fork 2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0){
        //cerramos extremo de escritura
        close(fd[1]);
        //redireccionamos el input ?
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        char c;
        while (read(STDIN_FILENO, &c, 1) > 0)
            write(STDOUT_FILENO, &c, 1);
    }
    
    wait(NULL);
    /*Else cuando solo tengo un child
    else{
        // Esto lo ejecuta el proceso padre

        //cerramos el extremo de escritura
        close(fd[1]);

        //leer los datos del pipe y mostrar en salida estandar
        char c;
        while (read(fd[0], &c, 1) > 0)
            write(STDOUT_FILENO, &c, 1);
        
        //esperamos que el child process termine
        wait(NULL);
    }*/
}