#include "minishell.h"

static char	*env_var_dup(t_var_env *env_list)
{
	int		i;
	int		index;
	char	*str_var;

	str_var = malloc((ft_strlen(env_list->name) + \
			ft_strlen(env_list->value) + 2) * sizeof(char));
	if (!str_var)
		return (NULL);
	i = 0;
	index = 0;
	while (env_list->name[i])
	{
		str_var[index++] = env_list->name[i++];
	}
	str_var[index++] = '=';
	i = 0;
	while (env_list->value[i])
	{
		str_var[index++] = env_list->value[i++];
	}
	str_var[index] = '\0';
	return (str_var);
}

char	**from_list_to_tab(t_var_env *env_list)
{
	char	**env_tab;
	int		i;

	env_tab = malloc(ft_size_env_list(env_list) * sizeof(char *));
	if (!env_tab)
		return (NULL);
	i = 0;
	while (env_list != NULL)
	{
		env_tab[i++] = env_var_dup(env_list);
		if (!env_tab[i - 1])
			return (NULL);
		env_list = env_list->next;
	}
	env_tab[i] = 0;
	return (env_tab);
}
