#include "minishell.h"

t_node	check_pipe(char *cmd)
{
	int		size;

	size = ft_strlen(cmd);
	if (size > 1)
		return ((t_node){T_ERROR, ft_strdup(cmd, 0, size)});
	return ((t_node){T_PIPE, ft_strdup(cmd, 0, size)});
}

t_node	check_redir(char *cmd)
{
	int		size;

	size = ft_strlen(cmd);
	if (size > 2)
		return ((t_node){T_ERROR, ft_strdup(cmd, 0, size)});
	if (size == 2)
	{
		if (cmd[0] == '>')
			return ((t_node){T_REDIR_OUT_APPEND, ft_strdup(cmd, 0, size)});
		return ((t_node){T_HEREDOC, ft_strdup(cmd, 0, size)});
	}
	else if (cmd[0] == '>')
		return ((t_node){T_REDIR_OUT, ft_strdup(cmd, 0, size)});
	else
		return ((t_node){T_REDIR_IN, ft_strdup(cmd, 0, size)});
}

int	check_unclosed(char *cmd)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	c = '\'';
	if (cmd[i] == '"')
		c = '"';
	while (cmd[i])
	{
		if (cmd[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_node	check_str(char *cmd)
{
	int		size;

	size = ft_strlen(cmd);
	if (check_unclosed(cmd) == FAIL)
		return ((t_node){T_ERROR, ft_strdup(cmd, 0, size)});
	return ((t_node){T_STR, ft_strdup(cmd, 0, size)});
}
