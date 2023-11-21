#include "minishell.h"

int	has_env_var(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ')
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
			has_env_var((*node_tab)[i].token) == SUCCESS)
			result += expand_or_empty(node_tab, i , env_list);
		i++;
	}
	if (result > 0)
		return (FAIL);
	return (SUCCESS);
}

char	*get_index_env_var(t_node **node_tab, int index, t_var_env **env_list)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while ((*node_tab)[index].token[i] && (*node_tab)[index].token[i] != '$')
		i++;
	start = i;
	while ((*node_tab)[index].token[i] && (*node_tab)[index].token[i] != ' ')
		i++;
	return (ft_strdup((*node_tab)[index].token, start, i));
}

int	expand_or_empty(t_node **node_tab, int index, t_var_env **env_list)
{
	char *name;

	name = get_name_env_var(node_tab, index, env_list);
	if (!name)
		return (FAIL);
	
	return (SUCCESS);
}

// regarde si STR ou STR double quote *OK
// regarde si il y a une variable d'env dans la str OK
// cherche le nom de la var dans le STR et check si la var existe
// si oui : fonction expand qui prend un nom et return la valeur de la variable remplace $name par cette valeur
// si non: remplace $name par un str vide ou vide : "" donc garder l'adresse du dollar en memoire ?