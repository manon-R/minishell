#include "minishell.h"

// void    display_pid_list(t_data *data)
// {
//     t_child_pid *tmp;

//     tmp = data->pid_list;
//     while (tmp != NULL)
//     {
//         ft_putstr_fd("pid = ", 1);
//         ft_putstr_nl_fd(ft_itoa((int)tmp->pid), 1);
//         tmp = tmp->next;
//     }
// }

void	append_pid(t_data *data, pid_t pid)
{
	t_child_pid	*new_elem;
	t_child_pid	*tmp;

	new_elem = malloc(sizeof(t_child_pid));
	if (!new_elem)
		return ;
	new_elem->pid = pid;
	new_elem->next = NULL;
	if (data->pid_list == NULL)
		data->pid_list = new_elem;
	else
	{
		tmp = data->pid_list;
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
}

int	exec_cmd(char *path, char **args, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), exit(EXIT_FAILURE), FAIL);
	append_pid(data, pid);
	if (pid == 0)
	{
		if ((*data).input_fd != STDIN_FILENO)
		{
			dup2((*data).input_fd, STDIN_FILENO);
			close((*data).input_fd);
		}
		if ((*data).output_fd != STDOUT_FILENO)
		{
			dup2((*data).output_fd, STDOUT_FILENO);
			close((*data).output_fd);
		}
		if (execve(path, args, NULL) == -1)
			perror("execve failed");
		return (free_all(args), free(path), SUCCESS);
	}
	return (SUCCESS);
}

int	exec_builtin(t_data *data, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), exit(EXIT_FAILURE), FAIL);
	append_pid(data, pid);
	if (pid == 0)
	{
		if ((*data).input_fd != STDIN_FILENO)
		{
			dup2((*data).input_fd, STDIN_FILENO);
			close((*data).input_fd);
		}
		if ((*data).output_fd != STDOUT_FILENO)
		{
			dup2((*data).output_fd, STDOUT_FILENO);
			close((*data).output_fd);
		}
		exit(builtin_list(data, args));
	}
	else
		return (builtin_parent(data, args));
	return (SUCCESS);
}
