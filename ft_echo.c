#include "minishell.h"

int	ft_echo(char **tab)
{
	int	i;
	int	opt;

	i = 1;
	opt = 0;
	if (tab[i] && ft_strcmp(tab[i], "-n") == SUCCESS)
	{
		opt++;
		i++;
	}
	while (tab[i] != NULL)
	{
		ft_putstr_fd(tab[i], STDOUT);
		if (tab[i + 1] && tab[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (opt == 0)
		write(1, "\n", 1);
	free_all(tab);
	return (SUCCESS);
}
