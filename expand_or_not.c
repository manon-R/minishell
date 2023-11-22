#include "minishell.h"

int	has_env_var(t_node previous_node, char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ' && \
			previous_node.type != T_HEREDOC)
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	check_env_var(t_node **node_tab, int size, t_var_env **env_list)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < size)
	{
		if ((is_str_double_quoted((*node_tab)[i]) == SUCCESS || \
			is_str((*node_tab)[i]) == SUCCESS) && \
			has_env_var((*node_tab)[i - 1], (*node_tab)[i].token) == SUCCESS)
			result += expand_or_empty(node_tab, i, env_list);
		i++;
	}
	if (result > 0)
		return (FAIL);
	return (SUCCESS);
}

char	*get_name_env_var(t_node **node_tab, int index)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while ((*node_tab)[index].token[i] && (*node_tab)[index].token[i] != '$')
		i++;
	i++;
	start = i;
	while ((*node_tab)[index].token[i] && (*node_tab)[index].token[i] != ' ')
		i++;
	return (ft_strdup((*node_tab)[index].token, start, i));
}

int	expand_or_empty(t_node **node_tab, int index, t_var_env **env_list)
{
	char	*name;
	char	*value;
	int		replace_space;

	name = get_name_env_var(node_tab, index);
	if (!name)
		return (FAIL);
	replace_space = ft_strlen(name) + 1;
	if (var_exist(*env_list, name) == FAIL)
		return (expand_var(node_tab, index, "", replace_space));
	value = take_value(*env_list, name);
	if (!value)
		return (FAIL);
	expand_var(node_tab, index, value, replace_space);
	if (has_env_var((*node_tab)[index - 1], \
		(*node_tab)[index].token) == SUCCESS)
		return (expand_or_empty(node_tab, index, env_list));
	return (SUCCESS);
}
// l63 +1 pour le $