#include "minishell.h"

void	display_env_list(t_var_env **env_list)
{
	t_var_env	*tmp;

	tmp = *env_list;
	while (tmp != NULL)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}
