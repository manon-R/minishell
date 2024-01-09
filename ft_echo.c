#include "minishell.h"

static int	is_option(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
		i++;
	else
		return (FAIL);
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	ft_echo(char **tab)
{
	int	i;
	int	opt;

	i = 1;
	opt = 0;
	if (tab[i] && ((is_option(tab[i]) == SUCCESS) \
		|| ft_strcmp(tab[i], "\"-n\"") == SUCCESS))
	{
		opt++;
		i++;
	}
	while (tab[i] != NULL)
	{
		if (is_option(tab[i]) != SUCCESS)
		{
			ft_putstr_fd(tab[i], STDOUT);
			if (tab[i + 1] && tab[i][0] != '\0')
				write(1, " ", 1);
		}	
		i++;
	}
	if (opt == 0)
		write(1, "\n", 1);
	free_all(tab);
	return (SUCCESS);
}
