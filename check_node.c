#include "minishell.h"

int	check_error_node(t_node **node_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((*node_tab)[i].type == T_ERROR && \
			check_unclosed((*node_tab)[i].token) == FAIL)
		{
			printf("minishell: %s  %s\n", UNCLOSED_ERROR, (*node_tab)[i].token);
			return (FAIL);
		}
		else if ((*node_tab)[i].type == T_ERROR && (i + 1) == size)
		{
			printf("minishell: %s \"%s\"\n", SYNTAX_ERROR, "newline");
			return (FAIL);
		}
		else if ((*node_tab)[i].type == T_ERROR)
		{
			printf("minishell: %s \"%s\"\n", SYNTAX_ERROR, (*node_tab)[i].token);
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
