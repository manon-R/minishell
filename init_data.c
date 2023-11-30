#include "minishell.h"

int	count_pipe(t_node **node_tab, int size)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (i < size)
	{
		if ((*node_tab)[i].type == T_PIPE)
			result++;
		i++;
	}
	return (result);
}

int	count_redir_cmd(t_data *data, t_node *node_tab)
{
	int	result;
	int	i;

	i = (*data).index;
	result = 0;
	(*data).nb_redir_in = 0;
	(*data).nb_redir_out = 0;
	while (i < (*data).size && node_tab[i].type != T_PIPE)
	{
		if (is_redir_node(node_tab[i]) == SUCCESS)
		{
			if (node_tab[i].type == T_HEREDOC || node_tab[i].type == T_REDIR_IN)
				(*data).nb_redir_in++;
			if (node_tab[i].type == T_REDIR_OUT || \
				node_tab[i].type == T_REDIR_OUT_APPEND)
				(*data).nb_redir_out++;
			result++;
		}
		i++;
	}
	return (result);
}

int	count_cmd(t_node **node_tab, int size)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (i < size)
	{
		if (((*node_tab)[i].type == T_STR && \
			ft_strlen((*node_tab)[i].token) > 0) || \
			(*node_tab)[i].type == T_HEREDOC)
			result++;
		i++;
	}
	return (result);
}

void	init_data(t_data *data, t_node **node_tab, int size)
{
	data->node_tab = node_tab;
	data->size = size;
	data->nb_pipe = count_pipe(node_tab, size);
	data->nb_cmd = count_cmd(node_tab, size);
	data->nb_redir_in = 0;
	data->nb_redir_out = 0;
	data->index = 0;
	data->start_cmd = 0;
}