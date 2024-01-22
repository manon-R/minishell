#include "minishell.h"

int	change_status_or_not(int status)
{
	if (status == IN_QUOTE)
		return (OUT_QUOTE);
	return (IN_QUOTE);
}

int	empty_cmd(t_data *data)
{
	(*data).ret = CMD_NOT_FOUND;
	ft_putstr_nl_fd("minishell: : command not found", 2);
	return (-1);
}

void	init_data_split(t_tabint *tab, int *node, t_data *data)
{
	*node = data->start_cmd;
	(*tab).status = OUT_QUOTE;
	(*tab).index = 0;
	(*tab).i = 0;
}

char	**extract_cmd(t_data *data)
{
	char	**result;

	result = split_cmd(data, data->node_tab);
	if (result == NULL)
		return (NULL);
	(*data).start_cmd = (*data).index;
	return (result);
}

	// int	i = 0;
	// ft_putstr_nl_fd("NEW COMMAND", 1);
	// while (result[i])
	// {
	// 	ft_putstr_nl_fd(result[i], 1);
	// 	i++;
	// }