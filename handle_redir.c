#include "minishell.h"

void	check_file(char const *file, int i)
{
	if (i == 1)
	{
		if (access(file, R_OK) != 0)
			perror(file);
	}
	else
	{
		if (access(file, F_OK) == 0)
		{
			if (access(file, W_OK) != 0)
				perror(file);
		}
	}
}

int	redir_in(t_node node, t_data *data)
{
	int	new_fd;

	check_file(node.token, 1);
	new_fd = open(node.token, O_RDONLY);
	if (new_fd < 0)
		return (FAIL);
	(*data).input_fd = new_fd;
	return (SUCCESS);
}

int	redir_out(t_node node, t_data *data)
{
	int	new_fd;

	check_file(node.token, 0);
	if (node.type == T_REDIR_OUT)
		new_fd = open(node.token, O_WRONLY | O_CREAT, 0644);
	else
		new_fd = open(node.token, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (new_fd < 0)
		return (FAIL);
	(*data).output_fd = new_fd;
	return (SUCCESS);
}

int	handle_heredoc(t_node node, t_data *data)
{
	int	new_fd;

	new_fd = append_heredoc(node.token);
	if (new_fd == FAIL)
		return (FAIL);
	(*data).input_fd = new_fd;
	return (SUCCESS);
}

void	handle_redir(t_data *data, t_node *node_tab)
{
	while ((*data).index < (*data).size && \
			node_tab[(*data).index].type != T_PIPE)
	{
		if (node_tab[(*data).index].type == T_HEREDOC)
		{
			if (handle_heredoc(node_tab[(*data).index], data) == FAIL)
				return ;
		}
		else if (node_tab[(*data).index].type == T_REDIR_IN)
		{
			if (redir_in(node_tab[(*data).index], data) == FAIL)
				return ;
		}
		else if (node_tab[(*data).index].type == T_REDIR_OUT)
		{
			if (redir_out(node_tab[(*data).index], data) == FAIL)
				return ;
		}
		else if (node_tab[(*data).index].type == T_REDIR_OUT_APPEND)
		{
			if (redir_out(node_tab[(*data).index], data) == FAIL)
				return ;
		}
		(*data).index++;
	}
	if (node_tab[(*data).index].type == T_PIPE)
		(*data).index++;
}
