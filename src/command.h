#ifndef COMMAND_H
# define COMMAND_H

/*Execute the command passed as argument*/
void  do_exec_call(char *com, char **envp);

/*execute last command*/
void exec_last_command(int ac, char **av, int fd[2], char **envp);
#endif