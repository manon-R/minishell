#include "minishell.h"

// static void	display_node_tab(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->size)
// 	{
// 		ft_putstr_fd("Token = ", 1);
// 		ft_putstr_nl_fd(data->node_tab[i]->token, 1);
// 		free(data->node_tab[i]->token);
// 		i++;
// 	}
// }

void	display_env_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		ft_putstr_nl_fd(tab[i], 1);
		free(tab[i]);
		i++;
	}
}

void	final_clean(t_data *data)
{
	free_pid_list(data->pid_list);
	data->pid_list = NULL;
	free_env_list(data);
	data->env_list = NULL;
	if (data->node_tab)
	{
		free_node_tab(data);
		data->node_tab = NULL;
	}
	free_all(data->env_tab);
	close((*data).input_fd);
	close((*data).output_fd);
}

void	clean_node_error(t_node **node_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((*node_tab)[i].token)
		{
			free((*node_tab)[i].token);
			(*node_tab)[i].token = NULL;
		}
		i++;
	}
}
