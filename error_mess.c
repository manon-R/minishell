#include "minishell.h"

void	display_error(char *cmd)
{
	ft_putstr_fd("minishell: export: « ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_nl_fd(" » : invalid identifier", STDERR);
}
