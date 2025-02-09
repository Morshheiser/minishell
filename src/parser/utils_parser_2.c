#include "../../include/minishell.h"

static int	ft_return_heredoc(int fd[2])
{
	printf("ft_return_heredoc: Closing fd[OUT] and returning fd[IN]\n");
	close (fd[OUT]);
	return (fd[IN]);
}

static int	ft_read_heredoc(int fd, char *end_of_file)
{
	char	*line;

	printf("ft_read_heredoc: Start reading from heredoc with end_of_file = \"%s\"\n", end_of_file);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("ft_read_heredoc: End of input (EOF) reached\n");
			break ;
		}
		if (!ft_strncmp(end_of_file, line, ft_strlen(end_of_file) + 1))
		{
			printf("ft_read_heredoc: End of file detected. Breaking loop.\n");
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

int	ft_heredoc(char *end_of_file)
{
	int	fd[2];

	printf("ft_heredoc: Creating pipe\n");
	if (pipe(fd) == -1)
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

	printf("ft_process_argument: Expanding argument at index %d\n", index);
	
	// Expansão de variáveis
	expanded = ft_expand_variables(args[index], shell->argv, shell->env->var_list);
	
	// Libera a memória do argumento original
	free(args[index]);

	// Verifica se a expansão falhou
	if (!expanded)
	{
		printf("ft_process_argument: Expansion failed, removing argument\n");

		// Removendo o argumento da lista (deslocando os elementos à esquerda)
		for (j = index; args[j]; j++)
			args[j] = args[j + 1];
		
		// Não há necessidade de continuar com este argumento
		return (0);
	}

	// Atualizando o argumento com o valor expandido
	args[index] = expanded;
	printf("ft_process_argument: Argument expanded to \"%s\"\n", expanded);

	return (1); // Expansão bem-sucedida
}

char	**ft_extract_command_arguments(char *line, t_shell *shell)
{
	char	**args;
	int		i;

	printf("ft_extract_command_arguments: Splitting line into arguments\n");
	args = ft_split_pipe(line, " \t\n\v\f\r");
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

	printf("ft_handle_redirection: Handling redirection in string \"%s\"\n", str);
	while (str[i] == '<' || str[i] == '>')
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\'' || str[i] == '"')
	{
		printf("ft_handle_redirection: Found quote, skipping to end\n");
		i += ft_find_quote_end(str + i) + 1;
	}
	else
		while (str[i] && !ft_strchr("<>| \t\n\v\r\f", str[i]))
			i++;
	ft_memset(str, ' ', i);
}

void	ft_clean_redirection_tokens(char *str)
{
	printf("ft_clean_redirection_tokens: Cleaning redirection tokens in string\n");
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

	printf("ft_create_new_command: Creating new command\n");
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
