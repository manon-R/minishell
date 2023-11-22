#include "minishell.h"

char	*extract_str(t_node node)
{
	int		i;
	int		start;
	int		status;

	i = 0;
	start = 0;
	status = OUT_QUOTE;
	if (node.token[i] && (node.token[i] == '\'' || node.token[i] == '"'))
	{
		i++;
		start = i;
		status = IN_QUOTE;
	}
	while (node.token[i] && ((node.token[i] != ' ' && status == OUT_QUOTE) || \
		((node.token[i] != '"' || node.token[i] != '\'') && status == IN_QUOTE)))
	{
		if ((node.token[i] == '"' || node.token[i] == '\'') && status == IN_QUOTE )
			status = OUT_QUOTE;
		i++;
	}
	if (node.token[i - 1] && (node.token[i - 1] == '\'' || node.token[i - 1] == '"'))
		i--;
	return (ft_strdup(node.token, start, i));
}

char	*update_token(t_node **node_tab, int index)
{
	int		i;
	int		j;
	char	*new_token;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (*node_tab)[index + 1].token;
	new_token = malloc(ft_strlen(tmp) - ft_strlen((*node_tab)[index].token));
	if (!new_token)
		return (0);
	while (tmp[i] && tmp[i] == (*node_tab)[index].token[i])
		i++;
	while (tmp[i] && tmp[i] == ' ')
		i++;
	while(tmp[i])
		new_token[j++] = tmp[i++];
	new_token[j] = '\0';
	free(tmp);
	return (new_token);
}

int	complete_redir_node(t_node **node_tab, int *size)
{
	int	i;

	i = 0;
	while (i < *size)
	{
		if (is_redir_node((*node_tab)[i]) == SUCCESS)
		{
			free((*node_tab)[i].token);
			(*node_tab)[i].token = extract_str((*node_tab)[i + 1]);
			if (!(*node_tab)[i].token)
				return (FAIL);
			(*node_tab)[i + 1].token = update_token(node_tab, i);
			if (!(*node_tab)[i + 1].token)
				return (FAIL);
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
