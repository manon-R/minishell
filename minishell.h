#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
// Besoin de compiler avec -lreadline
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

# define SUCCESS	0
# define FAIL		1
# define SPACES		" \t"
# define SEPARATORS "|><\n"

typedef enum e_token_type
{
	T_STR,
	T_VAR,
	T_REDIR_OUT = '>',
	T_REDIR_IN = '<',
	T_HEREDOC = '<' + 1,
	T_REDIR_OUT_APPEND = '>' + 1,
	T_PIPE = '|',
}					t_token_type;

typedef struct s_node
{
	int		type;
	char	*token;
}					t_node;

char	**ft_split(char *str);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen_tab(char **tab);
int		is_separators(char c);

void	free_all(char **content);

#endif