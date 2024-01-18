#include "minishell.h"

int	change_status_or_not(int status)
{
	if (status == IN_QUOTE)
		return (OUT_QUOTE);
	return (IN_QUOTE);
}

int	empty_cmd(t_data *data)
{
	(*data).ret = CMD_NOT_FOUND;
	ft_putstr_nl_fd("minishell: : command not found", 2);
	return (-1);
}

char	**split_cmd(t_data *data, t_node **node_tab)
{
	t_tabint	tab;
	int			node;
	int			size;
	char		**result;
	char		c;

	size = compute_size_cmd(data, data->node_tab);
	if (size < 0)
		return (NULL);
	result = malloc((size + 1) * sizeof(char *));
	if (!node_tab)
		return (NULL);
	if (!result)
		return (NULL);
	node = data->start_cmd;
	tab.status = OUT_QUOTE;
	tab.index = 0;
	tab.i = 0;
	while (node < data->index && node < data->size)
	{
		if ((*node_tab)[node].type == T_STR && ft_strlen((*node_tab)[node].token) != 0)
		{
			while ((*node_tab)[node].token[tab.i])
			{
				while ((*node_tab)[node].token[tab.i] && (*node_tab)[node].token[tab.i] == ' ')
					tab.i++;
				if ((*node_tab)[node].token[tab.i] == '"' || (*node_tab)[node].token[tab.i] == '\'' ) //boucle dans une fonction
				{
					c = (*node_tab)[node].token[tab.i];
					tab.start = tab.i;
					tab.i++;
					tab.status = change_status_or_not(tab.status);
					while ((*node_tab)[node].token[tab.i])
					{
						if (tab.status == OUT_QUOTE && (*node_tab)[node].token[tab.i + 1] && (*node_tab)[node].token[tab.i + 1] == ' ')
						{
							tab.i++;
							break;
						}
						if ((*node_tab)[node].token[tab.i] == c)
						{
							tab.status = change_status_or_not(tab.status);
							if (tab.status == OUT_QUOTE && (*node_tab)[node].token[tab.i + 1] && (*node_tab)[node].token[tab.i + 1] == ' ')
							{
								tab.i++;
								break;
							}
						}
						else if (tab.status == OUT_QUOTE && ((*node_tab)[node].token[tab.i] == '\'' || (*node_tab)[node].token[tab.i] == '"'))
						{
							c = (*node_tab)[node].token[tab.i];
							tab.status = change_status_or_not(tab.status);
						}
						tab.i++;
					}
					result[tab.index++] = ft_strdup((*node_tab)[node].token, tab.start, tab.i);
					if (!result[tab.index - 1])
						return (free_all(result), NULL);
				}
				else if ((*node_tab)[node].token[tab.i])
				{
					tab.start = tab.i;
					while ((*node_tab)[node].token[tab.i])
					{
						if ((*node_tab)[node].token[tab.i] == '"')
							tab.status = change_status_or_not(tab.status);
						if (tab.status == OUT_QUOTE && (*node_tab)[node].token[tab.i] == ' ')
							break ;
						tab.i++;
					}
					result[tab.index++] = ft_strdup((*node_tab)[node].token, tab.start, tab.i);
					if (!result[tab.index - 1])
						return (free_all(result), NULL);
				}
			}	
		}
		node++;
		tab.i = 0;
	}
	result[tab.index] = 0;
	return (result);
}

int	compute_size_cmd(t_data *data, t_node **node_tab)
{
	int		start;
	int		i;
	int		quote;
	int		size;
	char	c;

	start = data->start_cmd;
	quote = OUT_QUOTE;
	size = 0;
	i = 0;
	while (start < data->index && start < data->size)
	{
		if ((*node_tab)[start].type == T_STR && (ft_strlen((*node_tab)[start].token) != 0 || is_empty_cmd((*node_tab)[start].token) == SUCCESS))
		{
			if (is_empty_cmd((*node_tab)[start].token) == SUCCESS)
				return (empty_cmd(data));
			while ((*node_tab)[start].token[i])
			{
				while ((*node_tab)[start].token[i] && (*node_tab)[start].token[i] == ' ')
					i++;
				if ((*node_tab)[start].token[i] == '"' || (*node_tab)[start].token[i] == '\'' ) //boucle dans une fonction
				{
					c = (*node_tab)[start].token[i];
					size++;
					i++;
					quote = change_status_or_not(quote);
					while ((*node_tab)[start].token[i])
					{
						if (quote == OUT_QUOTE && (*node_tab)[start].token[i + 1] && (*node_tab)[start].token[i + 1] == ' ')
						{
							i++;
							break;
						}
						if ((*node_tab)[start].token[i] == c)
						{
							quote = change_status_or_not(quote);
							if (quote == OUT_QUOTE && (*node_tab)[start].token[i + 1] && (*node_tab)[start].token[i + 1] == ' ')
							{
								i++;
								break;
							}
						}
						else if (quote == OUT_QUOTE && ((*node_tab)[start].token[i] == '\'' || (*node_tab)[start].token[i] == '"'))
						{
							c = (*node_tab)[start].token[i];
							quote = change_status_or_not(quote);
						}
						i++;
					}
				}
				else if ((*node_tab)[start].token[i])
				{
					size++;
					while ((*node_tab)[start].token[i])
					{
						if ((*node_tab)[start].token[i] == '"')
							quote = change_status_or_not(quote);
						if (quote == OUT_QUOTE && (*node_tab)[start].token[i] == ' ')
						{
							i++;
							break ;
						}
						i++;
					}
				}
			}	
		}
		start++;
		i = 0;
	}
	return (size);
}

char	**extract_cmd(t_data *data)
{
	char	**result;

	result = split_cmd(data, data->node_tab);
	if (result == NULL)
		return (NULL);
	// int	i = 0;
	// ft_putstr_nl_fd("NEW COMMAND", 1);
	// while (result[i])
	// {
	// 	ft_putstr_nl_fd(result[i], 1);
	// 	i++;
	// }
	(*data).start_cmd = (*data).index;
	return (result);
}
