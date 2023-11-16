#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

# define SUCCESS		0
# define FAIL			1

# define SYNTAX_ERROR	"syntax error near unexpected token"
# define UNCLOSED_ERROR	"syntax error unclosed quote"

typedef enum e_token_type
{
	T_STR,
	T_REDIR_OUT,
	T_REDIR_IN,
	T_HEREDOC,
	T_REDIR_OUT_APPEND,
	T_PIPE,
	T_ERROR,
}					t_token_type;

typedef struct s_node
{
	int		type;
	char	*token;
}					t_node;

char	*ft_strcpy(char *dest, char *src, int start, int end);
char	*ft_strdup(char *src, int start, int end);

char	**ft_split(char *str);

int		check_unclosed(char *cmd);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *tab);
int		ft_strlen_tab(char **tab);
int		get_node_id_pipe(t_node **node_tab, int size);
int		get_node_id_redir(t_node **node_tab, int size);
int		is_separators(char c);

t_node	*lexer(char **cmd_tab);

void	free_all(char **content);
void	parser(t_node **node_tab, int size);

#endif