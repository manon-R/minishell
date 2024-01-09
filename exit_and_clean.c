#include "minishell.h"

void	display_node_tab(t_data *data)
{
	int i = 0;

	while (i < data->size)
	{
		ft_putstr_fd("Token = ", 1);
		ft_putstr_nl_fd(data->node_tab[i]->token, 1);
		free(data->node_tab[i]->token);
		i++;
	}
}

void	display_env_tab(char **tab)
{
	int i = 0;

	while (tab && tab[i])
	{
		// ft_putstr_fd("ENV VAR = ", 1);
		ft_putstr_nl_fd(tab[i],  1);
		free(tab[i]);
		i++;
	}
}

void	final_clean(t_data *data)
{
	free_pid_list(data->pid_list);
	free_env_list(data);
	free_node_tab(data);
	// display_env_tab(data->env_tab);
	// free_all(data->env_tab); = Deja free par execve??
}
