#include "minishell.h"

// void	append_pid(t_data *data, pid_t pid)
// {
// 	t_child_pid	*new_elem;
// 	t_child_pid	*tmp;

// 	new_elem = malloc(sizeof(t_child_pid));
// 	if (!new_elem)
// 		return ;//A coder une sortie exit and clean
// 	new_elem->pid = pid;
// 	new_elem->next = NULL;
// 	if ((*data).pid_list == NULL)
// 		(*data).pid_list = new_elem;
// 	else
// 	{
// 		tmp = (*data).pid_list;
// 		while (tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new_elem;
// 	}
// }

int exec_cmd(char *path, char **args, int fd_in, int fd_out)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) 
    {
        if (fd_in != STDIN_FILENO) 
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (fd_out != STDOUT_FILENO) 
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        if (execve(path, args, NULL) == -1) 
            perror("execve failed");
		return (free_all(args), free(path), SUCCESS);
    }
	return (SUCCESS);
}

int	exec_builtin(t_data *data, char **args, int fd_in, int fd_out)
{
	pid_t   pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) 
    {
        if (fd_in != STDIN_FILENO) 
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (fd_out != STDOUT_FILENO) 
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        builtin_list(data, args);
		exit(SUCCESS);
    }
    else
        builtin_parent(data, args);
		// (*data).env_tab = from_list_to_tab((*data).env_list); OU PAS?
    return (SUCCESS);
}
