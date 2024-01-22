#include "minishell.h"

void	free_all(char **content)
{
	int	i;

	i = 0;
	while (content && content[i])
	{
		if (content[i])
		{
			free(content[i]);
			content[i] = NULL;
		}
		i++;
	}
	if (content)
	{
		free(content);
		content = NULL;
	}
}

void	free_pid_list(t_child_pid *pid_list)
{
	t_child_pid	*tmp;

	while (pid_list && pid_list->next != NULL)
	{
		tmp = pid_list->next;
		free(pid_list);
		pid_list = NULL;
		pid_list = tmp;
	}
	if (pid_list)
	{
		free(pid_list);
		pid_list = NULL;
	}
}

void	free_node_tab(t_data *data)
{
	int	i;

	i = 0;
	if (!data->node_tab)
		return ;
	while (i < (*data).size)
	{
		if (data->node_tab && data->node_tab[i])
		{
			if (data->node_tab[i] && data->node_tab[i]->token)
				free(data->node_tab[i]->token);
			if (data->node_tab[i])
			{
				free(data->node_tab[i]);
				data->node_tab[i] = NULL;
			}
		}
		i++;
	}
}

void	free_env_list(t_data *data)
{
	t_var_env	*tmp;

	while (data->env_list != NULL)
	{
		tmp = data->env_list->next;
		free(data->env_list->name);
		free(data->env_list->value);
		free(data->env_list);
		data->env_list = NULL;
		data->env_list = tmp;
	}
	if (data->env_list)
	{
		free(data->env_list);
		data->env_list = NULL;
	}
}

void	free_pipefd(int **pipefd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pipefd && pipefd[i])
		{
			free(pipefd[i]);
			pipefd[i] = NULL;
		}
		i++;
	}
}

// void	free_envlist(t_var_env **env_list)
// {
// 	t_var_env	*tmp;
// 	t_var_env	*next;

// 	tmp = *env_list;
// 	while (tmp != NULL)
// 	{
// 		next = tmp->next;
// 		free(tmp->name);
// 		free(tmp->value);
// 		free(tmp);
// 		tmp = next;
// 	}
// 	if (env_list)
// 	{
// 		free(env_list);
// 		env_list = NULL;
// 	}
// }
