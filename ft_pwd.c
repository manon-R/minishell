#include "minishell.h"

int	ft_pwd(void)
{
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (FAIL);
	if (getcwd(buffer, BUFFER_SIZE) == NULL)
	{
		perror("Error");
		return (FAIL);
	}
	ft_putstr_nl_fd(buffer, STDOUT);
	free(buffer);
	return (SUCCESS);
}
