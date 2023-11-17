#include "minishell.h"

int	check_env_var(t_node **node_tab, int size, t_var_env **env_list)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < size)
	{
		if (is_str_double_quoted((*node_tab)[i]) == SUCCESS || is_str((*node_tab)[i]) == SUCCESS)
			result += expand_or_empty(node_tab, i , env_list);
		i++;
	}
	if (result > 0)
		return (FAIL);
	return (SUCCESS);
}

int	has_env_var(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] != ' ')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	expand_or_empty(t_node **node_tab, int index, t_var_env **env_list)
{
	int	start;

	if (has_env_var((*node_tab)[index].token) == FAIL)
		return (SUCCESS);
	else
	{
		start = get_index_env_var();
	}
	return (SUCCESS);
}

// regarde si STR ou STR double quote *OK
// cherche le nom de la var dans le STR et check si la var existe
// si oui : fonction expand qui prend un nom et return la valeur de la variable remplace $name par cette valeur
// si non: remplace $name par un str vide ou vide : "" donc garder l'adresse du dollar en memoire ?