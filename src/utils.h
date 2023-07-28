#ifndef UTILS_H
# define UTILS_H

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Get the full path for the passed command.
 *
 * If the command is already accessible does not search in PATH. If command is
 * not found in all the PATH directories, it errors out
 *
 * @param command The command to seach for.
 * @param envp    The environment variables from where to extract the PATH
 * @return char*  The correct path for the executable
 */
char	*get_path(char *command, char *envp[]);


#endif