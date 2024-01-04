#include "minishell.h"

int	valid_syntax(char *cmd)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	if (is_alpha(cmd[i]) == FAIL && cmd[i] != '_')
		return (FAIL);
	while (cmd[i])
	{
		if (cmd[i] == '=')
			equal++;
		i++;
	}
	if (equal > 0)
		return (SUCCESS);
	return (FAIL);
}

void	display_sort_env(t_data *data)
{
	int		i;
	char	**tab;

	tab = from_list_to_tab((*data).env_list);
	if (!tab)
		return ;
	sort_env_tab(tab);
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_nl_fd(tab[i], STDOUT);
		i++;
	}
	free_all(tab);
}

char	*extract_name(char *cmd)
{
	int		size;
	int		i;
	char	*name;

	size = get_index_equal(cmd);
	i = 0;
	name = malloc(size * sizeof(char));
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
	value = malloc(size * sizeof(char));
	if (!value)
		return (NULL);
	i++;
	while (cmd[i])
	{
		value[j] = cmd[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

int	ft_export(t_data *data, char **cmd)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	value = NULL;
	if (!cmd[i])
		return (display_sort_env(data), SUCCESS);
	while (cmd[i] && (*data).nb_pipe == 0)
	{
		if (valid_syntax(cmd[i]) == SUCCESS)
		{
			name = extract_name(cmd[i]);
			if (var_exist(data->env_list, name) == SUCCESS)
			{
				value = extract_value(cmd[i], name);
				if (value)
					udpate_env_var_value(data, name, value);
			}
			else
				append_list(data, cmd[i]);
		}
		i++;
	}
	return (free(name), free(value), SUCCESS);
}
