#include "minishell.h"

int	handle_pipeline(t_data *data, char **envp)
{
	int		(*pipefd)[2];
	int		j;
	int		i;
	int 	output_fd;
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
	int input_fd = STDIN_FILENO;
	while (i < (*data).nb_cmd) 
    {
		output_fd = (i == ((*data).nb_cmd - 1)) ? STDOUT_FILENO : pipefd[i][1];
		if (count_redir_cmd(data, *(data->node_tab)) > 0)
			handle_redir(data, &output_fd, &input_fd, *(data->node_tab));
		result = extract_cmd(data);
		path = process_path(result[0], envp);
		if (!path)
		{
            perror("path failed");
            exit(EXIT_FAILURE);
        }
		exec_cmd(path, result, input_fd, output_fd);
		if (i < (*data).nb_cmd - 1) 
		{
			close(pipefd[i][1]);  // Ferme l'extrémité d'écriture du pipe pour la commande actuelle
			input_fd = pipefd[i][0];  // Définir l'entrée pour la prochaine commande sur l'extrémité de lecture du pipe
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
    i = 0;
    while (i < (*data).nb_cmd) {
        wait(NULL);
        i++;
    } 
    return 0;
}
