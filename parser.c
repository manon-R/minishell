#include "minishell.h"


int	check_error_node(t_node **node_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((*node_tab)[i].type == T_ERROR)
		{
			printf("minishell: %s \"%s\"\n", SYNTAX_ERROR, (*node_tab)[i].token);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

void	parser(t_node **node_tab, int size)
{
	if (check_error_node(node_tab, size) == FAIL)
		return ;
	// if (complete_redir(node_tab, size) == FAIL)
	// 	return ;
	
}
