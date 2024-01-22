#include "minishell.h"

void	update_data(char *c, char value, t_tabint *tab)
{
	*c = value;
	(*tab).start = (*tab).i;
	(*tab).i++;
	(*tab).status = change_status_or_not((*tab).status);
}

void	update_param(t_quote *quote, char value)
{
	(*quote).value = value;
	(*quote).status = change_status_or_not(quote->status);
}

void	update_quote(char *c, char value, t_tabint *tab)
{
	*c = value;
	(*tab).status = change_status_or_not((*tab).status);
}
