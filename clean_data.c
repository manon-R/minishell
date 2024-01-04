#include "minishell.h"

void	free_all(char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i])
		{
			free(content[i]);
			content[i] = NULL;
		}
		i++;
	}
	if (content)
	{
		free(content);
		content = NULL;
	}
}
