#include "command.h"
#include "arguments.h"
#include <stdio.h>

void  do_exec_call(char *com, char **envp)
{
    char **arguments;
    (void) **envp;
   // char *command_path;

    arguments = get_argument_array(com);
    if (arguments == NULL || arguments[0] == NULL)
        perror("command parsing problem");
}