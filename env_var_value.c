#include "minishell.h"

char	*take_value( t_var_env *env_list, char *name)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == SUCCESS)
			return (ft_strdup(env_list->value, 0, ft_strlen(env_list->value)));
		env_list = env_list->next;
	}
	return (NULL);
}

int	expand_var(t_node **node_tab, int index, char *value, int name_size)
{
	int		final_size;
	int		i;
	int		j;
	int		elem;
	char	*tmp;

	i = 0;
	j = 0;
	elem = 0;
	final_size = ft_strlen((*node_tab)[index].token)- name_size + \
				ft_strlen(value);
	tmp = (*node_tab)[index].token;
	(*node_tab)[index].token = malloc(final_size + 1);
	if (!(*node_tab)[index].token)
		return (FAIL);
	while (tmp[i] && tmp[i] != '$')
	{
		if (tmp[i] == '"')
			i++;
		else
			(*node_tab)[index].token[elem++] = tmp[i++];
	}
	i += name_size;
	while (value[j])
		(*node_tab)[index].token[elem++] = value[j++];
	while (tmp[i])
	{
		if (tmp[i] == '"')
			i++;
		(*node_tab)[index].token[elem++] = tmp[i++];
	}
	(*node_tab)[index].token[elem] = '\0';
	free(tmp);
	return (SUCCESS);
}
