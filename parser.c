#include "minishell.h"


void	parser(t_node **node_tab, int size, t_var_env **env_list)
{
	check_redir_node(node_tab, size);
	check_pipe_node(node_tab, size);
	if (check_error_node(node_tab, size) == FAIL)
		return ;
	check_env_var(node_tab, size, env_list);
	// if (complete_redir_node(node_tab, size) == FAIL)
	// 	return ;
}

/* TO DO 
-> Variable d'environnement $ suivi de n'importe quoi
*/
