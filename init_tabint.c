#include "minishell.h"

void	init_tab(t_tabint	*tab)
{
	(*tab).i = 0;
	(*tab).index = 0;
	(*tab).status = OUT_QUOTE;
}
