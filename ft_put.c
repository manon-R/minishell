#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;
	int	status;
	int	c;

	i = 0;
	status = OUT_QUOTE;
	if (str && (str[i] == '"' || str[i] == '\''))
	{
		c = str[i++];
		status  = change_status_or_not(status);
	}
	while (str && str[i])
	{
		if (str[i] == c && status == IN_QUOTE)
		{
			status = change_status_or_not(status);
			i++;
		}
		else if ((str[i] == '"' || str[i] == '\'') && status == OUT_QUOTE)
		{
			c = str[i++];
			status = change_status_or_not(status);
		}
		else
			write(fd, &str[i++], 1);
	}
}

void	ft_putstr_nl_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
