#include "minishell.h"

static int	update_pwd(t_data *data, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_pwd)
		return (FAIL);
	if (getcwd(new_pwd, BUFFER_SIZE) == NULL)
	{
		perror("Error");
		return (FAIL);
	}
	if (var_exist(data->env_list, "OLDPWD") == SUCCESS)
		udpate_env_var_value(data, "OLDPWD", old_pwd);
	else
		append_list(data, ft_strjoin_classic("OLDPWD=", old_pwd));
	if (var_exist(data->env_list, "PWD") == SUCCESS)
		udpate_env_var_value(data, "PWD", new_pwd);
	else
		append_list(data, ft_strjoin_classic("PWD=", new_pwd));
	free(new_pwd);
	return (SUCCESS);
}

int	ft_cd(t_data *data, char **cmd)
{
	char	*old_pwd;

	if (cmd[2])
	{
		perror("minishell: cd: too many arguments");
		return (FAIL);
	}
	old_pwd =  malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!old_pwd)
		return (FAIL);
	if (getcwd(old_pwd, BUFFER_SIZE) == NULL)
		return (FAIL);
   	if (!cmd[1]) // Case cd
	{
		if (var_exist(data->env_list, "HOME") == SUCCESS)
		{
			if (chdir(take_value(data->env_list, "HOME")) != 0)
			{
				perror("minishell: cd: "); //bash: cd: truc: Aucun fichier ou dossier de ce type
				return (FAIL);
			}
			return (update_pwd(data, old_pwd));
		}
		else
		{
			perror("minishell: cd: \" HOME \" undefined");
			return (FAIL);
		}
	}
	if (chdir(cmd[1]) != 0)
	{
		perror("minishell: cd: "); //bash: cd: truc: Aucun fichier ou dossier de ce type
		return (FAIL);
	}
	update_pwd(data, old_pwd);
	return (SUCCESS);
}
