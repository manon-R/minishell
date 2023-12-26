#include "minishell.h"

int ft_env(t_data *data, char **cmd)
{
    if (cmd[1])
    {
        ft_putstr_fd("env: \"", STDERR);
        ft_putstr_fd(cmd[1], STDERR);
        ft_putstr_nl_fd("\": No such file or directory", STDERR);
        exit(CMD_NOT_FOUND);
    } 
    // display_env_list(&(*data).env_list);
    display_env_list(data->env_list);
    return (SUCCESS);
}
