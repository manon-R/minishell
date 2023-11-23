#include "minishell.h"

int	sub_lexer(char **cmd_tab, t_node **node_tab, int *i, int *index)
{
	if (cmd_tab[*i][0] == '|')
	{
		(*node_tab)[(*index)++] = check_pipe(cmd_tab[*i]);
		if (!(*node_tab)[*(index) - 1].token)
			return (FAIL);
	}
	else if (cmd_tab[*i][0] == '>' || cmd_tab[*i][0] == '<')
	{
		(*node_tab)[(*index)++] = check_redir(cmd_tab[*i]);
		if (!(*node_tab)[(*index) - 1].token)
			return (FAIL);
	}
	else
	{
		(*node_tab)[(*index)++] = check_str(cmd_tab[*i]);
		if (!(*node_tab)[(*index) - 1].token)
			return (FAIL);
	}
	(*i)++;
	return (SUCCESS);
}

t_node	*lexer(char **cmd_tab)
{
	int		i;
	int		index;
	t_node	*node_tab;

	i = 0;
	index = 0;
	node_tab = malloc(ft_strlen_tab(cmd_tab) * sizeof(t_node));
	while (cmd_tab && cmd_tab[i])
	{
		if (sub_lexer(cmd_tab, &node_tab, &i, &index) == FAIL)
			return (NULL);
	}
	return (node_tab);
}
/*
sécuriser le malloc du node_tab + 
ft_strdup en créant une fonction qui free le node_tab
*/