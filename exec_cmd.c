#include "minishell.h"

void exec_cmd(char *path, char **args, int fd_in, int fd_out)//, int pipefd[2]
{
    pid_t   pid;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        
        // Redirection de l'entrée standard si nécessaire
        if (fd_in != STDIN_FILENO) 
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        // Redirection de la sortie standard si nécessaire
        if (fd_out != STDOUT_FILENO) 
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        // Exécution de la commande
        if (execve(path, args, NULL) == -1) {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        free_all(args);
        free(path);
    }
}