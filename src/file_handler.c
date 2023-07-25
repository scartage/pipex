#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "file_handler.h"

/*dup2() se utiliza para redirigir un descriptor de archivo a otro. En este caso, estás redirigiendo in_fd (el descriptor de archivo del archivo que acabas de abrir) a STDIN_FILENO (la entrada estándar). Esto significa que cualquier lectura posterior de la entrada estándar (por ejemplo, a través de scanf, read, getchar, etc.) en este proceso se tomará en realidad del archivo.*/

/*Esto es lo que hace la función setup_infile_fds() en tu código. Toma el descriptor de archivo de un archivo que se ha abierto para lectura (in_fd), y redirige la entrada estándar del proceso a este archivo. También toma el extremo de escritura de un pipe (pfd[1]) y redirige la salida estándar del proceso a este pipe.

Una vez que se hace esto, cualquier lectura de la entrada estándar en este proceso se hará en realidad desde el archivo, y cualquier escritura en la salida estándar se hará en realidad en el pipe. Esto es útil, por ejemplo, si este proceso está a punto de ejecutar un nuevo programa con exec, y quieres que este nuevo programa lea su entrada de un archivo y escriba su salida a un pipe.*/
void set_infile_fds(int file_fd, int fd[2])
{
    if (dup2(file_fd, STDIN_FILENO) == -1)
        perror("dup2 STDIN_FILENO");
    if (dup2(fd[1], STDOUT_FILENO) == -1)
        perror("dup2 STDOUT_FILENO");
    close(file_fd);
    close(fd[0]);
    close(fd[1]);
}

int check_read_perm(char *path)
{
    int file_fd;
    
    //verifica existencia del archivo
    if (access(path, F_OK) == -1)
        perror("access error F_OK");
    //verifica permisos de lectura
    if (access(path, R_OK) == -1)
        perror("access error R_OK");
    file_fd = open(path, O_RDONLY);
    if (file_fd == -1)
        perror("open");
    return (file_fd);
}