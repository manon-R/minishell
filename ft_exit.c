#include "minishell.h"

int	only_digit(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_digit(cmd[i]) == FAIL && cmd[i] != '-' && cmd[i] != '+')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

long	ft_atoi(char *cmd)
{
	long	result;
	int			i;
	int			neg;

	result = 0;
	i = 0;
	neg = 1;
	if (cmd && ft_strlen(cmd) == 1 && cmd[0] == '0')
		return (0);
	if (cmd && cmd[i] && (cmd[i] == '-' || cmd[i] == '+'))
	{
		if (cmd[i] == '-')
			neg *= -1;
		i++;
	}
	while (cmd && is_digit(cmd[i]) == SUCCESS)
	{
		result = 10 * result + (cmd[i] - 48);
		i++;
	}
	return (result * neg);
}

int	is_valid(char *cmd) // only digit, < 9223372036854775808 && > -9223372036854775809 
{
	if (!cmd)
		return (FAIL);
	if (only_digit(cmd) == SUCCESS && ft_atoi(cmd) >= MIN_EXIT && ft_atoi(cmd) <= MAX_EXIT)
		return (SUCCESS);
	return (FAIL);
}

int	ft_exit(t_data *data, char **cmd)
{
	int	result;

	result = SUCCESS;
	if (data->nb_pipe == 0 || data->last == SUCCESS)
		ft_putstr_nl_fd("exit", STDERR);
	if (cmd[1] && cmd[2])
	{
		result = FAIL;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
	}
	if (cmd[1] && is_valid(cmd[1]) == FAIL)
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_nl_fd(" : numeric argument required", STDERR);
	}
	else if (cmd[1])
		result = ft_atoi(cmd[1]); // calcul a faire de 255 en 255
	free_all(cmd);
	return (result);
}