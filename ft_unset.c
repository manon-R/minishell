#include "minishell.h"

int	ft_unset(t_data *data, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{	
		if (var_exist(data->env_list, cmd[i]) == SUCCESS)
			del_env_var(data, cmd[i]);
		i++;
	}
	return (SUCCESS);
}
