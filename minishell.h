#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>


# define SUCCESS		0
# define FAIL			1

# define IN_QUOTE		42
# define OUT_QUOTE		-42

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
	char				*name;
	char				*value;
	struct s_var_env	*next;
}					t_var_env;

typedef struct s_tabint
{
	int	i;
	int	start;
	int	index;
	int	status;
}					t_tabint;

typedef struct s_data
{
	struct 	s_node **node_tab;
	int		size;
	int		nb_cmd;
	int		nb_pipe;
	int		nb_redir_in;
	int		nb_redir_out;
	int		index;
	int		start_cmd;
}					t_data;

char	*env_loop(char **envp, char *cmd);
char	*ft_strcpy(char *dest, char *src, int start, int end);
char	*ft_strdup(char *src, int start, int end);
char	*ft_strjoin(char *s1, char *s2);
char	*process_path(char *cmd, char **envp);
char	*simple_strdup(char *s);
char	*take_value( t_var_env *env_list, char *name);

char	**extract_cmd(t_data *data);
char	**from_list_to_tab(t_var_env *env_list);
char	**ft_split(char *str);
char	**simple_split(char *s, char c);


int		append_heredoc(char *delim);
int		append_list(t_var_env **env_list, char *var);
int		check_error_node(t_node **node_tab, int size);
int		check_env_var(t_node **node_tab, int size, t_var_env **env_list);
int		check_unclosed(char *cmd);
int		compute_size_cmd(t_data *data, t_node **node_tab);
int		count_redir_cmd(t_data *data, t_node *node_tab);
int		expand_or_empty(t_node **node_tab, int index, t_var_env **env_list);
int		expand_var(t_node **node_tab, int index, char *value, int name_size);
int		ft_size_env_list(t_var_env *env_list);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *tab);
int		ft_strlen_tab(char **tab);
int		get_node_id_pipe(t_node **node_tab, int size);
int		get_node_id_redir(t_node **node_tab, int size);
int		handle_pipeline(t_data *data, char **envp);
int		init_env_list(t_var_env **env_list, char **envp);
int		is_heredoc_node(t_node node);
int		is_redir_node(t_node node);
int		is_separators(char c);
int		is_space(char c);
int		is_str(t_node node);
int		is_str_double_quoted(t_node node);
int		is_str_single_quoted(t_node node);
int		var_exist(t_var_env *env_list, char *var_name);

t_node	check_pipe(char *cmd);
t_node	check_redir(char *cmd);
t_node	check_str(char *cmd);

t_node	*lexer(char **cmd_tab);

void	check_file(char const *file, int i);
void	check_pipe_node(t_node **node_tab, int size);
void	check_redir_node(t_node **node_tab, int size);
void	del_env_var(t_var_env **env_list, const char *name_del);
void	display_env_list(t_var_env **env_list);
void	exec_cmd(char *path, char **args, int fd_in, int fd_out);
void	free_all(char **content);
void	handle_redir(t_data *data, int *fd_out, int *fd_in, t_node *node_tab);
void	init_data(t_data *data, t_node **node_tab, int size);
void	init_tab(t_tabint	*tab);
void	parser(t_node **node_tab, int size, t_var_env **env_list);

#endif