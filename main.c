#include "minishell.h"

int	main (void)
{
	char	*buffer;
	char	**result;
	int		i;

	i = 0;
	result = NULL;
	buffer = malloc(10000);
	if (!buffer)
		return (0);
	while (1)
	{
		buffer = readline("minishell> ");
		if (ft_strcmp(buffer, "exit") == SUCCESS)
			return (free(buffer), SUCCESS);
		result = ft_split(buffer);
		while(i < ft_strlen_tab(result))
		{
			printf("%s\n", result[i]);
			i++;
		}
		free_all(result);
		free(buffer);
		i = 0;
	}

	return (0);
}