#include "minishell.h"

static int	is_valid_char(char c)
{
	if (is_digit(c) == FAIL && is_alpha(c) == FAIL && c != '_')
		return (FAIL);
	return (SUCCESS);
}

int	has_env_var(t_node previous_node, char *token)
{
	int	i;

	i = 0;
	while (token && token[i] && previous_node.token)
	{
		if (token[i] == '$' && token[i + 1] && \
			(is_valid_char(token[i + 1]) == SUCCESS || token[i + 1] == '?') && \
			previous_node.type != T_HEREDOC)
			return (SUCCESS);
		if (token[i] == '$' && token[i + 1] && (token[i + 1] == '"' || \
			token[i + 1] == '\''))
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	check_env_var(t_node **node_tab, int size, t_var_env **env_l, t_data *data)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < size)
	{
		if ((*node_tab)[i].token != NULL && ((i - 1) > 0 && (*node_tab)[i - 1].token) &&\
			(is_str_double_quoted((*node_tab)[i]) == SUCCESS || \
			is_str((*node_tab)[i]) == SUCCESS) && \
			has_env_var((*node_tab)[i - 1], (*node_tab)[i].token) == SUCCESS)
				result += expand_or_empty(node_tab, i, env_l, data);
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
	if ((*node_tab)[index].token[i] && \
		is_digit((*node_tab)[index].token[i]) == SUCCESS)
		return (ft_strdup((*node_tab)[index].token, start, i + 1));
	if ((*node_tab)[index].token[i] && ((*node_tab)[index].token[i] == '"' || \
		(*node_tab)[index].token[i] == '\''))
		return ("");
	if ((*node_tab)[index].token[i] && (*node_tab)[index].token[i] == '?')
		return (ft_strdup((*node_tab)[index].token, start, i + 1));
	while ((*node_tab)[index].token[i] && \
			is_valid_char((*node_tab)[index].token[i]) == SUCCESS)
		i++;
	return (ft_strdup((*node_tab)[index].token, start, i));
}

int	expand_or_empty(t_node **node_tab, int i, t_var_env **env_l, t_data *data)
{
	char	*name;
	char	*value;
	int		replace_space;

	name = get_name_env_var(node_tab, i);
	if (!name)
		return (FAIL);
	if (name[0] == '?')
		expand_var(node_tab, i, ft_itoa(data->ret), 2);
	else
	{
		replace_space = ft_strlen(name) + 1;
		if (var_exist(*env_l, name) == FAIL)
			expand_var(node_tab, i, "\0", replace_space);
		else
		{
			value = take_value(*env_l, name);
			if (!value)
				return (FAIL);
			expand_var(node_tab, i, value, replace_space);
		}
	}
	if (has_env_var((*node_tab)[i - 1], (*node_tab)[i].token) == SUCCESS)
		return (expand_or_empty(node_tab, i, env_l, data));
	return (SUCCESS);
}
