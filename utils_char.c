#include "minishell.h"

int	is_separators(char c)
{
	if (c == '\n' || c == '|' || c == '>' || c == '<')
		return (SUCCESS);
	return (FAIL);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (SUCCESS);
	return (FAIL);
}
