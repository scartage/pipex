#include "command.h"
#include "arguments.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

static void print_char_array(char **array) {
    int i = 0;
    while (array[i] != NULL) {
        printf("%s\n", array[i]);
        i++;
    }
}



void  do_exec_call(char *com, char **envp)
{
    char **arguments;
    char *command_path;

    arguments = get_argument_array(com);
    if (arguments == NULL || arguments[0] == NULL)
        perror("command parsing problem");
    command_path = get_path(arguments[0], envp);
    if (execve(command_path, arguments, envp) == -1)
        perror("Problem executing command");
    print_char_array(arguments); //no se ve en el output
}