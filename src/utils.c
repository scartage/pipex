#include "utils.h"

#define DEF "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

static char	*build_path(char *command, char *path)
{
	char	*temp;
	size_t	total_size;
	size_t	len;

	len = ft_strlen(path);
	total_size = ft_strlen(command) + len + 2;
	temp = malloc(total_size);
	if (!temp)
		perror("malloc fail in utils");
	ft_strlcpy(temp, path, total_size);
	ft_strlcpy(temp + len, "/", total_size);
	ft_strlcpy(temp + len + 1, command, total_size);
	return (temp);
}

static bool	check_exec_perm(char *command)
{
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (true);
		else
		{
			perror("permison denied");
			exit(126);
		}
	}
	return (false);
}

static char	*unquote_command(char *word)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(word);
	res = protected_malloc(len + 1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (word[i] == '\\' && (word[i + 1] == '\'' || word[i + 1] == '"'))
			i++;
		res[j++] = word[i++];
		if (word[i - 1] != '\\' && (word[i] == '\'' || word[i] == '"'))
			i++;
	}
	res[j] = 0;
	return (res);
}

//algo aqui puede fallar seguro, comparar y revisar
static char	**split_path(char *path)
{
	char	**result;

	result = ft_split(path, ':');
	if (!result)
		perror("malloc failed on split");
	return (result);
}

static char	**get_path_components(char *envp[])
{
	int		i;
	char	*temp;
	char	**result;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			temp = ft_substr(envp[i], 5, ft_strlen(envp[i]) + 1);
			if (!temp)
				perror("malloc failed on substr");
			result = split_path(temp);
			free(temp);
			return (result);
		}
		i++;
	}
	return (split_path(DEF));
}


static char	*search_path(char *command, char *envp[])
{
	char	*temp;
	char	**path;
	int		i;

	i = 0;
	path = get_path_components(envp);
	while (path[i])
	{
		temp = build_path(command, path[i]);
		if (check_exec_perm(temp))
		{
			ft_free_split(path);
			return (temp);
		}
		free(temp);
		i++;
	}
	ft_free_split(path);
	return (NULL);
}

char *get_path(char *command, char **envp){

    char *result;

    command = unquote_command(command);
    if (ft_strchr(command, '/') != NULL)
    {
        if (check_exec_perm(command))
            return (command);
        perror("No file or directory found");
        exit(EXIT_FAILURE);
    }
    result = search_path(command, envp);
    if (!result)
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    return (result);
}