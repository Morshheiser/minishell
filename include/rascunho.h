#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef enum e_token_type
{
	CMD = 2,
	CMD_ARG,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	IN_ARG,
	OUT_ARG,
	APPEND_ARG,
	HEREDOC_ARG,
	PIPE,
}		t_token_type;

typedef struct s_token
{
	struct s_token *prev;
	char *piece;
	t_token_type type;
	struct s_token *next;
} t_token;

typedef struct s_var_etc
{
	t_token **tokens_list;
	t_token **last_token;
	char *cmd;
}		t_var_etc;

/*-------------------------------------*/
typedef struct s_env_node
{
	struct s_env_node *prev;
	char *key;
	char *value;
	struct s_env_node *next;
}	t_env_node;

typedef struct s_env
{
	t_env_node *head;
	t_env_node *tail;
}	t_env;
/*--------------------------------------*/

typedef struct s_one_cmd
{
	char *cmd;
	int fd_in;
	int fd_out;
	pid_t pid;
	t_token *token_list;
} t_one_cmd;

typedef struct s_intro
{
	char *input;
	t_env env_list;
	t_one_cmd **cmds;
	int	pipe_fd[2];
}	t_intro;

void	go_minibash(t_intro *shell);

void	start_function(t_intro *shell, char **ev);
void parse_input(t_intro *shell);
/*----------------------------------------------------*/
void add_token(t_var_etc *etc, int start, int end, t_token_type type);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t len);

// int		vetor_size(char **ev);
// t_env_node	*new_env_node(char *key, char *value);
// void	env_addback(t_env *list, t_env_node *new_node);
// char	*get_env_content(char *ev, int sig);
void	get_env(t_env *list, char ** ev);

int		char_space(int c);
int		char_redirect(char c);
int		str_space(char *str);
void	change_flag(int c, int *single_flag, int *double_flag);
int		print_error(t_token_type type);

// int		invalid_pipe(char *str, int *i);
// int		check_pipes(char *str);
// int		check_quotes(char *str);
// int		error_input(char *input);
int		check_input(char *input);

// int		has_a_pair(const char *str);
// int		isop(const char *str);
// int		handle_quotes(char *str, int *i, int *flag);
// int		check_operators(char *str);
int		valid_input(char *str);

int count_pipe(char *str); //MUDAR NOME
// int out_of_quotes(int c, int *single_flag, int *double_flag);
// void get_pipe_piece(char *str, t_one_cmd **cmds, int *start, int *index, int current);
void split_pipe(char *str, t_one_cmd **cmds);

// void init_one_cmd(t_one_cmd *node);
// int	calculate_trim_bounds(char *str, int start, int len, int *trim_end);
t_one_cmd *create_cmd(char *str, int start, int len);

// void init_etc(t_var_etc *etc, t_token **tokens_list, t_token **last_token, char *cmd);
// void make_token_cmd(char *cmd, t_token **token_list, t_token **last);
void tokenizator(t_one_cmd **cmds, int p_count);

// void redirect_type(char *str, int start, t_token_type *redir_type, int *redir_len);
// void redirect_arg(t_var_etc *etc, int *current, t_token_type arg_type);
// t_token_type redir_arg_type(t_token_type redir_type);
void handle_redirect(t_var_etc *etc, int *current);
void handle_token(t_var_etc *etc, int *current, int *start, int *is_first_tk);

// void    free_tokens(t_token *token_list);
void	free_all_cmds(t_one_cmd ***cmds);
void	free_env_error(t_env **list, char **key, char **value);
void	free_env(t_env *list);

#endif