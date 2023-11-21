#include "minishell.h"

char	*extract_str()
{
	
}

int	complete_redir_node(t_node **node_tab, int *size)
{
	int	i;

	i = 0;
	while (i < *size)
	{
		if (is_redir_node((*node_tab)[i]) == SUCCESS)
		{
			printf("HERE post redir = %s\n", (*node_tab)[i + 1].token);
			free((*node_tab)[i].token);
			(*node_tab)[i].token = extract_str((*node_tab)[i + 1].token);
			//remplacer token par (*node_tab)[i + 1].token premier str et le reste sera une/des option
		}
		i++;
	}
	return (SUCCESS);
}

void	parser(t_node **node_tab, int size, t_var_env **env_list)
{
	check_redir_node(node_tab, size);
	check_pipe_node(node_tab, size);
	if (check_error_node(node_tab, size) == FAIL)
		return ;
	check_env_var(node_tab, size, env_list);
	if (complete_redir_node(node_tab, &size) == FAIL)
		return ;
}

/* TO DO 
-> Variable d'environnement $ suivi de n'importe quoi
*/
