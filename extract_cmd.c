#include "minishell.h"

// ls -la > out truc | echo hello
// (ls -la) (out) () (truc) | (echo hello)
// Boucler sur les nodes jusqu'au pipe => compter le nombre de str 
// puis Boucler sur les nodes jusqu'au pipe et split ["ls", "-la", "truc"] 
//=> boucler sur chaque token et split si space ou boucler si entre quote


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
	while(start < 3 && start < data->size) // au lieu de 4 => data->index 
	{
		printf("Before while token = %s\n", (*node_tab[start]).token);
		while ((*node_tab[start]).token[i])
		{
			while ((*node_tab[start]).token[i] && (*node_tab[start]).token[i] == ' ')
				i++;
			printf("After first while token[i] = %c\n", (*node_tab[start]).token[i]);
			if ((*node_tab[start]).token[i] == '\'' || (*node_tab[start]).token[i] == '"')
			{
				c = (*node_tab[start]).token[i];
				if (quote == OUT_QUOTE)
					quote = IN_QUOTE;
				else
					quote = OUT_QUOTE;
			}
			if (quote == IN_QUOTE)
			{
				size++;
				while ((*node_tab[start]).token[i] != c)
					i++;
			}
			else if ((*node_tab[start]).token[i] &&(*node_tab[start]).token[i] != ' ')
			{
				size++;
				while ((*node_tab[start]).token[i] && (*node_tab[start]).token[i] != ' ')
					i++;
			}
		}
		start++;
	}
	return (size);
}

char	**split_cmd(t_data *data)
{
	char	**result;
	int		size;

	size = compute_size_cmd(data, data->node_tab);
	result = malloc(size);
	if (!result)
		return (NULL);
	printf("SIZE = %d\n", size);





	data->start_cmd = data->index;
	return (result);
}