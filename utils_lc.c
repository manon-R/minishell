#include "minishell.h"

static int	get_index_equal(char *var)
{
	int	i;

	i = 0;
	while(var[i] != '=')
		i++;
	return (i);
}

void	del_env_var(t_var_env **env_list, const char *name_del)
{
	t_var_env	*tmp;
	t_var_env	*new_next;

	tmp = *env_list;
	while (tmp->next!= NULL)
	{
		if (ft_strcmp(tmp->next->name, name_del) == SUCCESS)
		{
			new_next = tmp->next->next;
			free(tmp->next->name);
			free(tmp->next->value);
			free(tmp->next);
			if (new_next->next != NULL)
				tmp->next = new_next->next;
			else
				tmp->next = NULL;
			free(new_next->name);
			free(new_next->value);
			free(new_next);
		}
		else
			tmp = tmp->next;
	}
}
//Etre sur que la variable existe avant d'appeler cette fonction / Ici FAIL si n'existe pas
int	udpate_env_var_value(t_var_env **env_list, const char *var_name, char *new_value)
{
	t_var_env	*tmp;

	tmp = *env_list;
	while (tmp != NULL && ft_strcmp(tmp->name, var_name) == FAIL)
		tmp = tmp->next;
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = ft_strdup(new_value, 0, ft_strlen(new_value));
		if (!tmp->value)
			return (FAIL);
		return (SUCCESS);
	}
	return (FAIL);
}


int	append_list(t_var_env **env_list, char *var)
{
	t_var_env	*new_elem;
	t_var_env	*temp;
	int			index_equal;

	new_elem = NULL;
	new_elem = malloc(sizeof(t_var_env));
	if (!new_elem)
		return (FAIL);
	index_equal = get_index_equal(var);
	new_elem->name = ft_strdup(var, 0, index_equal);
	new_elem->value = ft_strdup(var, (index_equal + 1), ft_strlen(var));
	if (!new_elem->name || !new_elem->value)
		return (FAIL);
	new_elem->next = NULL;
	if (*env_list == NULL)
		*env_list = new_elem;
	else
	{
		temp = *env_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_elem;
	}
	return (SUCCESS);
}

int	init_env_list(t_var_env **env_list, char **envp)
{
	int			i;

	i = 0;
	*env_list = NULL;
	while (envp && envp[i])
	{
		if (append_list(env_list, envp[i]) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

// Export : besoin de savoir si on veut creer ou modifier 