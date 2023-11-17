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

typedef struct s_var_env
{
	char	*name;
	char	*value;
	struct s_var_env	*next;
}					t_var_env;

char	*ft_strcpy(char *dest, char *src, int start, int end);
char	*ft_strdup(char *src, int start, int end);

char	**from_list_to_tab(t_var_env *env_list);
char	**ft_split(char *str);

int		append_list(t_var_env **env_list, char *var);
int		check_error_node(t_node **node_tab, int size);
int		check_env_var(t_node **node_tab, int size, t_var_env **env_list);
int		check_unclosed(char *cmd);
int		ft_size_env_list(t_var_env *env_list);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *tab);
int		ft_strlen_tab(char **tab);
int		get_node_id_pipe(t_node **node_tab, int size);
int		get_node_id_redir(t_node **node_tab, int size);
int		init_env_list(t_var_env **env_list, char **envp);
int		is_redir_node(t_node node);
int		is_separators(char c);
int		is_str(t_node node);
int		is_str_double_quoted(t_node node);
int		is_str_single_quoted(t_node node);
int		var_exist(t_var_env *env_list, char *var_name);

t_node		*lexer(char **cmd_tab);

void	check_pipe_node(t_node **node_tab, int size);
void	check_redir_node(t_node **node_tab, int size);
void	del_env_var(t_var_env **env_list, const char *name_del);
void	display_env_list(t_var_env **env_list);
void	free_all(char **content);
void	parser(t_node **node_tab, int size, t_var_env **env_list);

#endif