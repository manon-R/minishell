#include "minishell.h"

int	get_index_equal(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (i == ft_strlen(var))
		return (0);
	return (i);
}

void	del_env_var(t_data *data, char *name_del)
{
	t_var_env	*tmp;
	t_var_env	*new_next;

	tmp = data->env_list;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (ft_strcmp(tmp->next->name, name_del) == SUCCESS)
		{
			new_next = tmp->next->next;
			free(tmp->next->name);
			free(tmp->next->value);
			free(tmp->next);
			if (new_next != NULL)
				tmp->next = new_next;
			else
				tmp->next = NULL;
		}
		else if (tmp->next)
			tmp = tmp->next;
		else
			tmp = NULL;
	}
}

int	udpate_env_var_value(t_data *data, char *var_name, char *new)
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
		free(tmp->value);
		tmp->value = ft_strdup(new, 0, ft_strlen(new));
		if (!tmp->value)
			return (FAIL);
		return (SUCCESS);
	}
	return (FAIL);
}

int	append_list(t_data *data, char *var)
{
	t_var_env	*new_elem;
	t_var_env	*temp;
	int			index_equal;

	new_elem = NULL;
	new_elem = malloc(sizeof(t_var_env));
	if (!new_elem)
		return (FAIL);
	index_equal = get_index_equal(var);
	if (var[index_equal - 1] == '+')
	new_elem->name = ft_strdup(var, 0, index_equal - 1);
	else
		new_elem->name = ft_strdup(var, 0, index_equal);
	new_elem->value = ft_strdup(var, (index_equal + 1), ft_strlen(var));
	if (!new_elem->name || !new_elem->value)
		return (FAIL);
	new_elem->next = NULL;
	if (data->env_list == NULL)
		data->env_list = new_elem;
	else
	{
		temp = data->env_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_elem;
	}
	return (SUCCESS);
}

int	init_env_list(t_data *data, char **envp)
{
	int			i;

	i = 0;
	while (envp && envp[i])
	{
		if (append_list(data, envp[i]) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
