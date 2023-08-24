#include "file_handler.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>

int check_read_perm(char *path)
{
    int file_fd;

    // verifica existencia del archivo
    if (access(path, F_OK) == -1)
        perror("access error F_OK");
    // verifica permisos de lectura
    if (access(path, R_OK) == -1)
        perror("access error R_OK");
    //lo abrimos con intencion de leer, de aqui sacamos el pid
    file_fd = open(path, O_RDONLY);
    if (file_fd == -1)
        perror("open");
    return (file_fd);
}

/*Esta función toma un path y una bandera is_heredoc, y verifica si se puede escribir en el archivo en la ruta dada. Si is_heredoc es true, se abre el archivo para escribir en modo adjunto; de lo contrario, se abre para escribir en modo truncado. La función devuelve el descriptor de archivo (fd) o -1 si hay un error.*/
int check_write_perm(char *path, bool is_heredoc)
{
    int fd;

    if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
        perror("in access from check_write_perm");
    if (is_heredoc)
        fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        perror("fd == -1 in check_write_perm");
    return (fd);
}

void set_outfile_fd(char *outfile, int fd[2], bool is_heredoc)
{
    int temp_fd;

    temp_fd = check_write_perm(outfile, is_heredoc);
    if (dup2(temp_fd, STDOUT_FILENO) == -1)
        perror("redirecting stdou to file");
    if (dup2(fd[0], STDIN_FILENO) == -1)
        perror("redirecting pipe to stdin");
    if (close(fd[1]) == -1)
        perror("closing write end pipe");
    if (close(temp_fd) == -1)
        perror("closing outfile");
}

/*dup2() se utiliza para redirigir un descriptor de archivo a otro. En este caso, estás redirigiendo in_fd (el descriptor de archivo del archivo que acabas de abrir) a STDIN_FILENO (la entrada estándar). Esto significa que cualquier lectura posterior de la entrada estándar (por ejemplo, a través de scanf, read, getchar, etc.) en este proceso se tomará en realidad del archivo.*/
/*Esto es lo que hace la función setup_infile_fds() en tu código. Toma el descriptor de archivo de un archivo que se ha abierto para lectura (in_fd), y redirige la entrada estándar del proceso a este archivo. También toma el extremo de escritura de un pipe (pfd[1]) y redirige la salida estándar del proceso a este pipe.
Una vez que se hace esto, cualquier lectura de la entrada estándar en este proceso se hará en realidad desde el archivo, y cualquier escritura en la salida estándar se hará en realidad en el pipe. Esto es útil, por ejemplo, si este proceso está a punto de ejecutar un nuevo programa con exec, y quieres que este nuevo programa lea su entrada de un archivo y escriba su salida a un pipe.*/

/*todo esto esta pasando dentro de un fork,
primero, la entrada estandar se cambia para que se lea desde
el archivo input, segundo, la salida de este proceso se escribira
en la salida de escritura del pipe, se cierra la salida de lectura
ya que no se hace uso de este*/

void set_infile_fds(int file_fd, int fd[2])
{
    /*int outfile_fd = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd == -1){
        perror("Error al abrir el archivo de salida");
        exit(EXIT_FAILURE);
    }*/
    if (dup2(file_fd, STDIN_FILENO) == -1)
        perror("dup2 STDIN_FILENO");
    //redirigimos la salida del proceso al extremo de escritura del pipe
    //cualquier cosa que se envie a la salida se escribira en el pipe
    if (dup2(fd[1], STDOUT_FILENO) == -1)
        perror("dup2 STDOUT_FILENO");
    //en este proceso solo escribe en el pipe, no se lee
     /*close(outfile_fd);*/

    if (close(fd[0]) == -1)
        perror("closing read end pipe");
}
