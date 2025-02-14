#include "../../include/minishell.h"
/*
static int	ft_return_heredoc(int fd[2])
{
	printf("ft_return_heredoc: Closing fd[OUT] and returning fd[IN]\n");
	close (fd[OUT]);
	return (fd[IN]);
}*/

static int	ft_read_heredoc(int fd, char *end_of_file)
{
	char	*line;
	size_t eof_len;

	eof_len = ft_strlen(end_of_file);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_perror(0,"ft_read_heredoc: End of input (EOF) reached\n", end_of_file);
			return (1);
		}
		if (!ft_strncmp(end_of_file, line, eof_len))
			break ;
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	return (0);
}

int	ft_heredoc(char *end_of_file)
{
	int	fd[2];

	if (pipe(fd))
	{
		ft_perror(0, "heredoc", 0);
		return (-1);
	}
	ft_read_heredoc(fd[OUT], end_of_file);
	close(fd[OUT]);
	return (fd[IN]);
}

t_cmd	*ft_command_error(t_fd *in, t_fd *out, char **split)
{
	printf("ft_command_error: Cleaning up split and file descriptors\n");
	split = ft_clean_split(split);
	ft_clean_fd(in);
	ft_clean_fd(out);
	return (0);
}

static int	ft_process_argument(char **args, int index, t_shell *shell)
{
	char	*expanded;
	int		j;

	expanded = ft_expand_variables(args[index], shell->argv, shell->env->var_list);
	free(args[index]);
	if (!expanded)
	{
		printf("ft_process_argument: Expansion failed, removing argument\n");
		j = index;
		while(args[j])
		{
			args[j] = args[j + 1];
			j++;
		}
		return (0);
	}
	args[index] = expanded;
	return (1);
}

char	**ft_extract_command_arguments(char *line, t_shell *shell)
{
	char	**args;
	int		i;

	args = ft_split_with_set(line, " \t\n\v\f\r");
	if (!args)
	{
		printf("ft_extract_command_arguments: Failed to split line into arguments\n");
		return (NULL);
	}
	i = 0;
	while (args[i])
	{
		if (!ft_process_argument(args, i, shell))
			continue;
		i++;
	}
	return (args);
}

static void	ft_handle_redirection(char *str)
{
	int i = 0;

	while (str[i] == '<' || str[i] == '>')
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\'' || str[i] == '"')
		i += ft_find_quote_end(str + i) + 1;
	else
		while (str[i] && !ft_strchr("<>| \t\n\v\r\f", str[i]))
			i++;
	ft_memset(str, ' ', i);
}

void	ft_clean_redirection_tokens(char *str)
{
	while (*str)
	{
		str += ft_find_quote_end(str);
		if (*str == '<' || *str == '>')
			ft_handle_redirection(str);
		else if (*str >= 9 && *str <= 13)
			*str = ' ';
		str++;
	}
}

t_cmd	*ft_create_new_command(t_fd *in, t_fd *out, char **args)
{
	t_cmd	*arg;

	arg = ft_calloc(sizeof(t_cmd), 1);
	if (arg)
	{
		arg->fdin.ffd = in->ffd;
		arg->fdin.fnm = in->fnm;
		arg->fdout.ffd = out->ffd;
		arg->fdout.fnm = out->fnm;
		arg->args = args;
		arg->next = 0;
	}
	return (ft_check_alloc(arg, "create_new_command"));
}

char **ft_split_with_set(char *line, const char *set)
{
    char **split;
    int i = 0;
    int len;
    int num_words;

    split = ft_allocate_split(line, set);
    if (!split)
        return NULL;
    num_words = ft_count_word(line, set);
    while (i < num_words)
    {
        while (ft_strchr(set, *line))
            line++;
        len = ft_len_word(line, set);
        split[i] = ft_sub_word(line, len);
        if (!*(split)[i])
            return (ft_free_splterr(split));
        line += len;
        i++;
    }
    split[i] = NULL;
    return split;
}

char **ft_allocate_split(char *line, const char *set)
{
    char **split;
    int words;

    if (!line || !set)
        return NULL;
    words = ft_count_word(line, set);
    split = ft_calloc(words + 1, sizeof(char *));
    return split;
}