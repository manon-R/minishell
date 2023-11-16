#include "minishell.h"

void	free_all(char **content)
{
	int	i;

	i = 0;
	while (content && content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
}
