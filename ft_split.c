#include "minishell.h"

int	is_separators(char c)
{
	if (c == '\n' || c == '|' || c == '>' || c == '<')
		return (SUCCESS);
	return (FAIL);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (SUCCESS);
	return (FAIL);
}

int	compute_size(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]) == SUCCESS)
			i++;
		if (str[i] && is_space(str[i]) == FAIL)
		{
			size++;
			while (str[i] && is_separators(str[i]) == FAIL)
				i++;
			if (is_separators(str[i]) == SUCCESS)
			{
				i++;
				size++;
			}
		}
	}
	return (size);
}

char	*ft_strdup(char *src, int start, int end)
{
	char	*dest;
	int		size_src;

	size_src = end - start;
	dest = malloc((size_src + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	return (ft_strcpy(dest, src, start, end));
}

char	**ft_split(char *str)
{	
	char	**new_tab;
	int		i;
	int		start;
	int		index;
	int		status;

	i = 0;
	index = 0;
	status = OUT_QUOTE;
	new_tab = malloc((compute_size(str) + 1) * sizeof(char *));
	if (!new_tab)
		return (0);
	while (str[i])
	{
		while (str[i] && is_space(str[i]) == SUCCESS)
			i++;
		if (str[i] && is_space(str[i]) == FAIL)
		{
			start = i;
			while (str[i])
			{
				if ((str[i] == '"' || str[i] == '\'') && status == OUT_QUOTE)
					status = IN_QUOTE;
				else if((str[i] == '"' || str[i] == '\'') && status == IN_QUOTE)
					status = OUT_QUOTE;
				else if (is_separators(str[i]) == SUCCESS && status == OUT_QUOTE)
					break;
				i++;
			}
			if (i != start)
			{
				new_tab[index++] = ft_strdup(str, start, i);
				if (!new_tab[index - 1])
					return (free_all(new_tab), NULL);
			}
			if (str[i] && is_separators(str[i]) == SUCCESS)
			{
				start = i;
				while (str[i] && is_separators(str[i]) == SUCCESS)
					i++;
				new_tab[index++] = ft_strdup(str, start, i);
				if (!new_tab[index - 1])
					return (free_all(new_tab), NULL);
			}
		}
	}
	new_tab[index] = 0;
	return (new_tab);
}
