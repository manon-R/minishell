#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "echo") == SUCCESS || \
		ft_strcmp(cmd, "cd") == SUCCESS || \
		ft_strcmp(cmd, "pwd") == SUCCESS || \
		ft_strcmp(cmd, "export") == SUCCESS || \
		ft_strcmp(cmd, "unset") == SUCCESS || \
		ft_strcmp(cmd, "env") == SUCCESS || \
		ft_strcmp(cmd, "exit") == SUCCESS))
		return (SUCCESS);
	return (FAIL);
}

int	builtin_list(t_data *data, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == SUCCESS)
		return (ft_echo(cmd));
	// if (ft_strcmp(cmd[0], "cd") == SUCCESS)
	// 	return (ft_cd(cmd));
	// if (ft_strcmp(cmd[0], "pwd") == SUCCESS)
	// 	return (ft_pwd(cmd)); //si > 1 args ils sont ignores
	if (ft_strcmp(cmd[0], "export") == SUCCESS) // A FAIRE a chaque export ou unset data.env_tab = from_list_to_tab(data.env_list);
		ft_export(data, cmd);
	if (ft_strcmp(cmd[0], "unset") == SUCCESS)
		ft_unset(data, cmd);
	if (ft_strcmp(cmd[0], "env") == SUCCESS)
		ft_env(data, cmd);
	if (ft_strcmp(cmd[0], "exit") == SUCCESS)
		return (ft_exit(data, cmd));
	return (SUCCESS);
}

/*
 echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/