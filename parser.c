#include "minishell.h"


void	parser(t_node **node_tab, int size)
{
	if (check_error_node(node_tab, size) == FAIL)
		return ;
	if (check_redir_node(node_tab, size) == FAIL)
		return ;
	if (check_pipe_node(node_tab, size) == FAIL)
		return ;
	// if (complete_redir_node(node_tab, size) == FAIL)
	// 	return ;
}

/* TO DO 
-> Variable d'environnement $ suivi de n'importe quoi
-> Verif que tout est bien free en cas d'erreur
*/
