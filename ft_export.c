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

void	sort_env_tab(char **env_tab)
{
	int		i;
	int		sorted;
	int		size;
	char	*tmp;

	sorted = 0;
	size = ft_strlen_tab(env_tab);
	while (env_tab && sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(env_tab[i], env_tab[i + 1]) > 0)
			{
				tmp = env_tab[i];
				env_tab[i] = env_tab[i + 1];
				env_tab[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
		size--;
	}
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
	// free_all(tab);
}

char *extract_name(char *cmd)
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

char *extract_value(char *cmd)
{
	int		size;
	int		i;
	char	*value;

	i = get_index_equal(cmd);
	size = ft_strlen(cmd + i);
	value = malloc(size * sizeof(char));
	if (!value)
		return (NULL);
	i++;
	while (i < size)
	{
		value[i] = cmd[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

int	ft_export(t_data *data, char **cmd)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (!cmd[i])
	{
		display_sort_env(data); // env trié par ordre alphabétique + declare -x devant cf bash
		return (SUCCESS);
	}
	while (cmd[i] && (*data).nb_pipe == 0)
	{
		if (valid_syntax(cmd[i]) == SUCCESS)
		{
			name = extract_name(cmd[i]);
			if (var_exist((*data).env_list, name) == SUCCESS)
			{
				value = extract_value(cmd[i]);
				ft_putstr_nl_fd(value, STDOUT);
				if (value)
					udpate_env_var_value(&(*data).env_list, name, value);
			}
			else
				append_list(&data->env_list, cmd[i]);
			(*data).env_tab = from_list_to_tab((*data).env_list);
		}
		i++;
	}
	free(name);
	free(value);
	return (SUCCESS);
}
