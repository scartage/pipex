#include "command.h"
#include "arguments.h"
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
    (void) **envp;
   // char *command_path;

    arguments = get_argument_array(com);
    if (arguments == NULL || arguments[0] == NULL)
        perror("command parsing problem");
    print_char_array(arguments);
    
}