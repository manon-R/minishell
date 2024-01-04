#include "minishell.h"

void	sort_env_tab(char **env_tab)
{
	int		i;
	int		sorted;
	int		size;
	char	*tmp;

	sorted = 0;
	size = ft_strlen_tab(env_tab);
	while (env_tab && sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(env_tab[i], env_tab[i + 1]) > 0)
			{
				tmp = env_tab[i];
				env_tab[i] = env_tab[i + 1];
				env_tab[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
		size--;
	}
}
