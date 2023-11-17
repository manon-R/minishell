#include "minishell.h"


void	parser(t_node **node_tab, int size)
{
	check_redir_node(node_tab, size);
	check_pipe_node(node_tab, size);
	if (check_error_node(node_tab, size) == FAIL)
		return ;
	// expand_env_var();
	// if (complete_redir_node(node_tab, size) == FAIL)
	// 	return ;
}

/* TO DO 
-> Variable d'environnement $ suivi de n'importe quoi
*/
