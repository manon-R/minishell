#include "minishell.h"

static int	display_error_message(char *error, char *str, int code_error)
{
	if (code_error == 1)
	{
		ft_putstr_fd("minishell: ", STDOUT);
		ft_putstr_fd(error, STDOUT);
		ft_putstr_fd(" ", STDOUT);
		ft_putstr_nl_fd(str, STDOUT);
		return (FAIL);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDOUT);
		ft_putstr_fd(error, STDOUT);
		ft_putstr_fd(" \"", STDOUT);
		ft_putstr_fd(str, STDOUT);
		ft_putstr_nl_fd(" \"", STDOUT);
		return (MISUSE);
	}
}

int	check_error_node(t_node **node_tab, int size, t_data *data)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((*node_tab)[i].type == T_ERROR && \
			check_unclosed((*node_tab)[i].token) == FAIL)
		{
			(*data).ret = display_error_message(UNCLOSED_ERROR, (*node_tab)[i].token, 1);
			return (FAIL);
		}
		else if ((*node_tab)[i].type == T_ERROR && (i + 1) == size)
		{
			(*data).ret = display_error_message(SYNTAX_ERROR, "newline", 2);
			return (FAIL);
		}
		else if ((*node_tab)[i].type == T_ERROR)
		{
			(*data).ret = display_error_message(SYNTAX_ERROR, (*node_tab)[i].token, 2);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

void	check_redir_node(t_node **node_tab, int size)
{
	const int	redir_id = get_node_id_redir(node_tab, size);

	if (redir_id >= 0)
	{
		if ((redir_id + 1) == size)
		{
			(*node_tab)[redir_id].type = T_ERROR;
			return ;
		}
		if ((*node_tab)[redir_id + 1].type == T_HEREDOC || \
			(*node_tab)[redir_id + 1].type == T_REDIR_IN || \
			(*node_tab)[redir_id + 1].type == T_REDIR_OUT || \
			(*node_tab)[redir_id + 1].type == T_REDIR_OUT_APPEND || \
			(*node_tab)[redir_id + 1].type == T_PIPE)
		{
			(*node_tab)[redir_id].type = T_ERROR;
			return ;
		}
	}
}

void	check_pipe_node(t_node **node_tab, int size)
{
	const int	redir_id = get_node_id_pipe(node_tab, size);

	if (redir_id >= 0)
	{
		if ((redir_id + 1) == size)
		{
			(*node_tab)[redir_id].type = T_ERROR;
			return ;
		}
		if ((*node_tab)[redir_id + 1].type == T_PIPE)
		{
			(*node_tab)[redir_id].type = T_ERROR;
			return ;
		}
	}
}
