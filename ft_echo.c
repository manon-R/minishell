#include "minishell.h"

static int	is_option(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "\"-n\"") == SUCCESS)
		return (SUCCESS);
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
	int	word;

	i = 1;
	opt = 0;
	word = 0;
	if (tab[i] && is_option(tab[i]) == SUCCESS)
	{
		opt++;
		i++;
	}
	while (tab[i] != NULL)
	{
		if (is_option(tab[i]) != SUCCESS || (is_option(tab[i]) == SUCCESS && word > 0))
		{
			ft_putstr_fd(tab[i], STDOUT);
			word++;
			if (tab[i + 1])
				write(1, " ", 1);
		}	
		i++;
	}
	if (opt == 0)
		write(1, "\n", 1);
	free_all(tab);
	return (SUCCESS);
}
