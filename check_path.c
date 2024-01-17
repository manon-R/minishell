#include "minishell.h"

int	is_directory(char *cmd)
{
	struct stat	fileInfo;

	// Utilisez la fonction stat pour obtenir des informations sur le fichier/dossier
	stat(cmd, &fileInfo);
	// Vérifiez si le chemin correspond à un répertoire
	if (S_ISDIR(fileInfo.st_mode))
		return (SUCCESS);
	return (FAIL);
}

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
		if (is_directory(cmd) == SUCCESS)
			return (display_error_dir(cmd), NULL);
		path = check_absolute_path(cmd);
		if (!path)
			return (perror(cmd), NULL);
	}
	else
		path = env_loop(envp, cmd);
	return (path);
}
