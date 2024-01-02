#include "minishell.h"

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
		pipefd = malloc(((*data).nb_cmd - 1) * sizeof(int[2]));
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
		if (result[0])
		{
			if (ft_strcmp(result[0], "exit") == SUCCESS && (*data).last == SUCCESS)
				(*data).exit = SUCCESS;
			if (is_builtin(result[0]) == SUCCESS)
				(*data).ret = exec_builtin(data, result);
			else
			{
				path = process_path(result[0], (*data).env_tab);
				if (path)
					(*data).ret = exec_cmd(path, result, data);
			}
		}
		if (i < (*data).nb_cmd - 1) 
		{
			close(pipefd[i][1]); // Ferme l'extrémité d'écriture du pipe pour la commande actuelle
			(*data).input_fd = pipefd[i][0];  // Définir l'entrée pour la prochaine commande sur l'extrémité de lecture du pipe
		}
        i++;
    }
    // Parent 
    // Ferme toutes les extrémités de pipes dans le parent
    i = 0;
    while (i < (*data).nb_cmd - 1) {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
        i++;
    }
    // Attends que tous les processus enfants se terminent
    // i = 0;
    // while (i < (*data).nb_cmd) {
    //     wait(NULL);
    //     i++;
    // }
	// t_child_pid *tmp;
    // // i = 0;
	// tmp = data->pid_list;
	// while (tmp != NULL)
	// {
	// 	// if (i < (*data).nb_cmd - 1)
	// 	// {
	// 	// 	close(pipefd[i][0]);
    //     // 	close(pipefd[i][1]);
	// 	// }
	// 	waitpid(tmp->pid, NULL, 0);
	// 	// i++;
	// 	tmp = tmp->next;
	// }
	//clean all
    return (data->ret);
}
