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

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (SUCCESS);
	return (FAIL);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (SUCCESS);
	return (FAIL);
}
