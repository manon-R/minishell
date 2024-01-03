#include "minishell.h"

int g_exit_code = 0;

void	ft_ctrl_c_exit(int i)
{
	(void)i;
	exit(1);
}

static void	write_readline_to_pipe(int pipefd[2], char *delimiter)
{
	char	*next_line;
	int		len_next_line;

	signal(SIGINT, &ft_ctrl_c_exit);
	close(pipefd[0]);
	next_line = malloc(BUFFER_SIZE);
	next_line = readline("> ");
	len_next_line = ft_strlen(next_line);
	while (next_line && (ft_strcmp(next_line, delimiter) == FAIL || len_next_line != ft_strlen(delimiter)))
	{
		if (write(pipefd[1], next_line, len_next_line) == -1)
			perror(NULL);
		if (write(pipefd[1], "\n", 1) == -1)
			perror(NULL);
		free(next_line);
		next_line = readline("> ");
		len_next_line = ft_strlen(next_line);
	}
	if (next_line != NULL)
		free(next_line);
	close(pipefd[1]);
	exit(SUCCESS);
}

int	append_heredoc(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		exit_status;

	if (pipe(pipefd) == -1)
	{
		perror(NULL);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		close(pipefd[1]);
		close(pipefd[0]);
		return (-1);
	}
	if (pid == 0)
    {
		write_readline_to_pipe(pipefd, delimiter);
    	return (pipefd[0]);
    }
	waitpid(pid, &exit_status, 0);
	close(pipefd[1]);
	return (pipefd[0]);
}

