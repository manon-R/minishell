#include "minishell.h"

static int	get_index_equal(char *var)
{
	int	i;

	i = 0;
	while(var[i] != '=')
		i++;
	return (i);
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

// supprimer une variable / unset
// creer = append ou remplacer une variable / export 
// Export : besoin de savoir si on veut creer ou modifier 

