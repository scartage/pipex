#ifndef FILE_HANDLER_H
# define FILE_HANDLER_H

/*Set up the file descriptors for the first command.
It redirects the output from the stdout to write end of the pipe,
and then read to be from the file instead of the stdin*/
void set_infile_fds(int file_fd, int fd[2]);

//Check read permissions and opens file
int check_read_perm(char *path);

#endif