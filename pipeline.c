#include "minishell.h"

int	is_dir_or_cmdnotfound(char *path)
{
	if (is_directory(path) == SUCCESS)
		return (PERM_DENY);
	return (CMD_NOT_FOUND);
}

int	handle_pipeline(t_data *data)
{
	int		(*pipefd)[2];
	int		j;
	int		i;
	char	*path;
	char	**result;

	i = 0;
	j = 0;
	if ((*data).nb_pipe > 0)
	{
		pipefd = (int (*)[2]) malloc((((*data).nb_cmd - 1) * 2) * sizeof(int));
		if (!pipefd)
			return (FAIL);
		while (j < ((*data).nb_cmd - 1))
		{
			if (pipe(pipefd[j]) == -1)
			{
				perror("pipe");
				return (FAIL);
			}
			j++;
		}
	}
	(*data).input_fd = STDIN_FILENO;
	while (i < (*data).nb_cmd)
	{
		if (i == (*data).nb_cmd - 1)
		{
			(*data).last = SUCCESS;
			(*data).output_fd = STDOUT_FILENO;
		}
		else
			(*data).output_fd = pipefd[i][1];
		if (count_redir_cmd(data, *(data->node_tab)) > 0)
			handle_redir(data, *(data->node_tab));
		result = extract_cmd(data);
		if (result == NULL)
			break ;
		else if (result[0] && data->input_fd >= 0 && data->output_fd > 0)
		{
			if (ft_strcmp(result[0], "exit") == SUCCESS && \
				(*data).last == SUCCESS && !result[2] && (*data).nb_pipe == 0)
				(*data).exit = SUCCESS;
			if (is_builtin(result[0]) == SUCCESS)
				(*data).ret = exec_builtin(data, result);
			else
			{
				path = process_path(result[0], (*data).env_tab);
				if (path)
					(*data).ret = exec_cmd(path, result, data);
				else
					(*data).ret  = is_dir_or_cmdnotfound(result[0]);
			}
		}
		if (i < (*data).nb_cmd - 1)
		{
			close(pipefd[i][1]);// Ferme l'extrémité d'écriture du pipe pour la commande actuelle
			(*data).input_fd = pipefd[i][0];// Définir l'entrée pour la prochaine commande sur l'extrémité de lecture du pipe
		}
		i++;
		free_all(result);
	}
	// Parent : Ferme toutes les extrémités de pipes dans le parent
	i = 0;
	while (i < (*data).nb_cmd - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	// Attends que tous les processus enfants se terminent
	t_child_pid *tmp;
	int	status;
	tmp = data->pid_list;
	while (tmp != NULL)
	{
		waitpid(tmp->pid, &status, 0); //tmp->pid
		tmp = tmp->next;
	}
	if (WIFEXITED(status) && (*data).ret == 0) 
		(*data).ret = WEXITSTATUS(status);
	// free_pipefd((int **)pipefd, (*data).nb_cmd - 1);
	return (data->ret);
}
