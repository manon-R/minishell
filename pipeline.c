#include "minishell.h"

int	is_dir_or_cmdnotfound(char *path)
{
	if (is_directory(path) == SUCCESS)
		return (PERM_DENY);
	return (CMD_NOT_FOUND);
}

int	is_empty_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "\"\"") == SUCCESS || ft_strcmp(cmd, "") == SUCCESS || \
		ft_strcmp(cmd, "''") == SUCCESS || ft_strcmp(cmd, " ") == SUCCESS)
		return (SUCCESS);
	return (FAIL);
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
	path = NULL;
	result = NULL;
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
			if ((*data).output_fd != STDOUT_FILENO && (*data).output_fd > 0)
				close((*data).output_fd);
			(*data).output_fd = STDOUT_FILENO;
		}
		else
			(*data).output_fd = pipefd[i][1];
		if (count_redir_cmd(data, *(data->node_tab)) > 0)
		{
			if (handle_redir(data, *(data->node_tab)) == FAIL)
				break ;
		}
		result = extract_cmd(data);
		if (result == NULL)
			break ;
		else if (result[0] && data->input_fd >= 0 && data->output_fd > 0)
		{
			if ((*data).nb_pipe > 0 && i < (*data).nb_cmd - 1)
				(*data).pipe_0 = pipefd[i][0];
			if (is_empty_cmd(result[0]) == SUCCESS)
				empty_cmd(data);
			else
			{
				if (ft_strcmp(result[0], "exit") == SUCCESS && \
					(*data).last == SUCCESS && ft_strlen_tab(result) <= 2 && \
					(*data).nb_pipe == 0)
					(*data).exit = SUCCESS;
				if (is_builtin(result[0]) == SUCCESS)
				{
					(*data).ret = exec_builtin(data, result);
					free_all(result);
					result = NULL;
				}
				else if ((ft_strcmp(result[0], ":") == SUCCESS || \
						ft_strcmp(result[0], "!") == SUCCESS) && \
						ft_strlen(result[0]) == 1)
				{
					(*data).ret = SUCCESS;
					free_all(result);
					result = NULL;
				}
				else
				{
					path = process_path(result[0], (*data).env_tab);
					if (path)
						(*data).ret = exec_cmd(path, result, data);
					else
						(*data).ret = is_dir_or_cmdnotfound(result[0]);
					if ((*data).last == FAIL && result)
					{
						free_all(result);
						result = NULL;
					}
				}
			}
		}
		if (data->input_fd < 0 || data->output_fd < 0)
		{
			free_all(result);
			result = NULL;
		}
		if (i < (*data).nb_cmd - 1)
		{
			close(pipefd[i][1]);
			if ((*data).input_fd != STDIN)
				close((*data).input_fd);
			(*data).input_fd = pipefd[i][0];
		}
		i++;
	}
	free_all(result);
	result = NULL;
	i = 0;
	while (i < (*data).nb_cmd - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	t_child_pid	*tmp;
	int			status;
	tmp = data->pid_list;
	status = 0;
	while (tmp != NULL)
	{
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(status) && (*data).ret == 0) 
		(*data).ret = WEXITSTATUS(status);
	if ((*data).nb_pipe > 0)
		free(pipefd);
	free_pid_list(data->pid_list);
	data->pid_list = NULL;
	if ((*data->node_tab) != NULL)
	{
		free_simple_node((*data->node_tab), (*data).size);
		data->node_tab = NULL;
	}
	if ((*data).input_fd != STDIN)
		close((*data).input_fd);
	if ((*data).output_fd != STDOUT && (*data).output_fd > 0)
		close((*data).output_fd);
	return (data->ret);
}
