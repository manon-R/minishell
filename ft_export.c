#include "minishell.h"

int	valid_syntax(char *cmd, int size)
{
	int	i;

	i = 0;
	if (is_alpha(cmd[i]) == FAIL && cmd[i] != '_')
		return (display_error(cmd, "export"), FAIL);
	i++;
	if (size == 0)
		size = ft_strlen(cmd);
	while (cmd[i] && i < size)
	{
		if (i == size - 1 && (cmd[i] == '+' || is_digit(cmd[i]) == SUCCESS || \
			is_alpha(cmd[i]) == SUCCESS))
			i++;
		else if (i != size - 1 && (is_digit(cmd[i]) == SUCCESS || \
				is_alpha(cmd[i]) == SUCCESS || cmd[i] == '_'))
			i++;
		else
			return (display_error(cmd, "export"), FAIL);
	}
	return (SUCCESS);
}

char	*extract_name(char *cmd)
{
	int		size;
	int		i;
	char	*name;

	size = get_index_equal(cmd);
	i = 0;
	if (cmd[size - 1] == '+')
		size--;
	name = malloc((size + 1) * sizeof(char));
	if (!name)
		return (NULL);
	while (i < size)
	{
		name[i] = cmd[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*extract_value(char *cmd, char *name)
{
	int		size;
	int		i;
	int		j;
	char	*value;

	i = get_index_equal(cmd);
	j = 0;
	size = ft_strlen(cmd) - ft_strlen(name);
	if (is_double_quote(cmd, i) == SUCCESS)
		size -= 2;
	value = malloc(size * sizeof(char));
	if (!value)
		return (NULL);
	i++;
	while (cmd && cmd[i])
	{
		if (cmd[i] != '"')
		{
			value[j] = cmd[i];
			j++;
		}
		i++;
	}
	value[j] = '\0';
	return (value);
}

int	append_env_var_value(t_data *data, char *var_name, char *new)
{
	t_var_env	*tmp;

	tmp = data->env_list;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, var_name) == SUCCESS)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		tmp->value = ft_strjoin_classic(tmp->value, new);
		if (!tmp->value)
			return (free(tmp->value), FAIL);
		return (SUCCESS);
	}
	return (FAIL);
}

int	ft_export(t_data *data, char **cmd)
{
	int		i;
	int		fail;
	char	*name;
	char	*value;

	i = 1;
	fail = 0;
	name = NULL;
	value = NULL;
	if (!cmd[i])
		return (display_sort_env(data), SUCCESS);
	while (cmd && cmd[i] && (*data).nb_pipe == 0)
	{
		if (valid_syntax(cmd[i], get_index_equal(cmd[i])) == SUCCESS)
		{
			if (get_index_equal(cmd[i]) == 0)
				return (SUCCESS);
			name = extract_name(cmd[i]);
			if (var_exist(data->env_list, name) == SUCCESS)
			{
				value = extract_value(cmd[i], name);
				if (value && has_plus_equal(cmd[i]) == FAIL)
					udpate_env_var_value(data, name, value);
				else if (value)
					append_env_var_value(data, name, value);
			}
			else if (append_list(data, cmd[i]) == FAIL)
				fail++;
		}
		else
			fail++;
		i++;
		free(name);
		name = NULL;
		free(value);
		value = NULL;
	}
	if (fail > 0)
		return (free(name), free(value), free_env_list(data), \
				data->env_list = NULL, FAIL);
	return (free(name), free(value), SUCCESS);
}
