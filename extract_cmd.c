#include "minishell.h"

// ls -la > out truc | echo hello
// (ls -la) (out) () (truc) | (echo hello)
// Boucler sur les nodes jusqu'au pipe => compter le nombre de str 
// puis Boucler sur les nodes jusqu'au pipe et split ["ls", "-la", "truc"] 
//=> boucler sur chaque token et split si space ou boucler si entre quote

int	split_cmd(char **result, t_data *data, t_node **node_tab)
{
	t_tabint	tab;
	int			node;
	char c;

	node = data->start_cmd;
	tab.status = OUT_QUOTE;
	tab.index = 0;
	tab.i = 0;
	while(node < data->index && node < data->size) // au lieu de 4 => data->index 
	{
		if ((*node_tab)[node].type == T_STR && ft_strlen((*node_tab)[node].token) != 0)
		{
			while ((*node_tab)[node].token[tab.i])
			{
				while ((*node_tab)[node].token[tab.i] && (*node_tab)[node].token[tab.i] == ' ')
					tab.i++;
				if ((*node_tab)[node].token[tab.i] && ((*node_tab)[node].token[tab.i] == '\'' || (*node_tab)[node].token[tab.i] == '"'))
				{
					c = (*node_tab)[node].token[tab.i];
					if (tab.status == OUT_QUOTE)
					{
						tab.status = IN_QUOTE;
						tab.start = tab.i;
					}
					else
						tab.status = OUT_QUOTE;
					tab.i++;
				}
				if (tab.status == IN_QUOTE)
				{
					while ((*node_tab)[node].token[tab.i] && (*node_tab)[node].token[tab.i] != c)
						tab.i++;
					tab.i++;
					tab.status = OUT_QUOTE;
					result[tab.index++] = ft_strdup((*node_tab)[node].token, tab.start, tab.i);
					if (!result[tab.index - 1])
						return (free_all(result), FAIL);
				}
				else if ((*node_tab)[node].token[tab.i] && (*node_tab)[node].token[tab.i] != ' ')
				{
					tab.start = tab.i;
					while ((*node_tab)[node].token[tab.i] && (*node_tab)[node].token[tab.i] != ' ')
						tab.i++;
					result[tab.index++] = ft_strdup((*node_tab)[node].token, tab.start, tab.i);
					if (!result[tab.index - 1])
						return (free_all(result), FAIL); // Verif si leaks		
				}
			}
		}
		node++;
		tab.i = 0;
	}
	result[tab.index] = 0;
	return (SUCCESS);
}


int	compute_size_cmd(t_data *data, t_node **node_tab)
{
	int	start;
	int	i;
	int	quote;
	int	size;
	char c;

	start = data->start_cmd;
	quote = OUT_QUOTE;
	size = 0;
	i = 0;
	while(start < data->index && start < data->size) // au lieu de 4 => data->index 
	{
		if ((*node_tab)[start].type == T_STR && ft_strlen((*node_tab)[start].token) != 0)
		{
			while ((*node_tab)[start].token[i])
			{
				while ((*node_tab)[start].token[i] && (*node_tab)[start].token[i] == ' ')
					i++;
				if ((*node_tab)[start].token[i] && ((*node_tab)[start].token[i] == '\'' || (*node_tab)[start].token[i] == '"'))
				{
					c = (*node_tab)[start].token[i];
					if (quote == OUT_QUOTE)
						quote = IN_QUOTE;
					else
						quote = OUT_QUOTE;
					i++;
				}
				if (quote == IN_QUOTE)
				{
					size++;
					while ((*node_tab)[start].token[i] && (*node_tab)[start].token[i] != c)
						i++;
				}
				else if ((*node_tab)[start].token[i] && (*node_tab)[start].token[i] != ' ')
				{
					size++;
					while ((*node_tab)[start].token[i] && (*node_tab)[start].token[i] != ' ')
						i++;
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
	int		size;
	// int		i;

	size = compute_size_cmd(data, data->node_tab);
	result = malloc((size + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (split_cmd(result, data, data->node_tab) == FAIL)
		return (NULL);
	// i = 0;
	// while(i < size)
	// {
	// 	printf("Result[%d] = %s \n", i, result[i]);
	// 	i++;
	// }
	data->start_cmd = data->index;
	return (result);
}