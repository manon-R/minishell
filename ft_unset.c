#include "minishell.h"

int	ft_unset(t_data *data, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i])
	{	
		if (var_exist((*data).env_list, cmd[i]) == SUCCESS)
		{
			del_env_var(&(*data).env_list, cmd[i]);
			free_all((*data).env_tab);
			(*data).env_tab = from_list_to_tab((*data).env_list);
		}
		i++;
	}
	return (SUCCESS);
}
