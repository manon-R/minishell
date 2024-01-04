#include "minishell.h"

static int	is_path(char *cmd)
{
	int		i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '/')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

static char	*check_absolute_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

char	*process_path(char *cmd, char **envp)
{
	char	*path;

	if (is_path(cmd) == SUCCESS)
	{
		path = check_absolute_path(cmd);
		if (!path)
			return (perror(cmd), NULL);
	}
	else
		path = env_loop(envp, cmd);
	return (path);
}
