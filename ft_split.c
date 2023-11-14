#include "minishell.h"

int	is_separators(char c)
{
	int	i;

	i = 0;
	while (SEPARATORS[i] != '\0')
	{
		if (c == SEPARATORS[i])
			return (SUCCESS);
		i++;	
	}
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
		while (is_separators(str[i]) == SUCCESS)
			i++;
		if (str[i] && is_separators(str[i]) == FAIL)
		{
			size++;
			while (str[i] && is_separators(str[i]) == FAIL)
				i++;
		}
	}
	return (size);
}

char	*ft_strcpy(char *dest, char *src, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
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

	i = 0;
	index = 0;
	new_tab = malloc((compute_size(str) + 1) * sizeof(char *));
	if (!new_tab)
		return (0);
	while (str[i])
	{
		while (is_separators(str[i]) == SUCCESS)
			i++;
		if (str[i] && is_separators(str[i]) == FAIL)
		{
			start = i;
			while (str[i] && is_separators(str[i]) == FAIL)
				i++;
			new_tab[index] = ft_strdup(str, start, i);
			index++;
		}
	}
	new_tab[index] = 0;
	return (new_tab);
}
