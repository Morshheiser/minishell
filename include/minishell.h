#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct s_env
{
	char	*key;
	char	*str;
	struct s_env	*next;
}			t_env;

typedef struct s_token
{
	char	*token;
	char	*first_cmd;
	char	cmd;
	char	*path;
	struct s_token	*next;
}			t_token;

enum
{
	ERROR = 0,
	NOTERROR = 1,
	ERROR_QUOTE = 2,
	ERROR_WORD = 3,
};

//split_function
char	*word_between_spaces(char *str, int idx);
void	split_free(char **str, size_t o);
char    **mod_split_input(char *str);

//split_utils
int is_space(int c);
int find_next_char(char *str, int idx);
size_t  word_count(char *str);
int all_quotes_has_end(char *str);

//input_start_function
void    start_function(char **ev);

//input_checker_functions
int input_check(char *str);

//input_tokenizator
int do_tokens(char *rd_input);

//env_functions
static int	first_equal(char *str);
t_env	*new_env_lst(char **ev, t_env *env_list);

//env_utils
t_env	*my_lstlast(t_env *lst);
void	my_lstadd_back(t_env **lst, t_env *new);
t_env	*my_lstnew(char *first_str, char *second_str);
void	free_env(t_env *list);

#endif
