#include "minishell.h"

int	var_exist(t_var_env *env_list, char *var_name)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, var_name) == SUCCESS)
			return (SUCCESS);
		env_list = env_list->next;
	}
	return (FAIL);
}
