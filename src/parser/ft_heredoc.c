#include "../../include/minishell.h"

//ok

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


static int	ft_return_heredoc(int fd[2])
{
    close (fd[OUT]);
    return (fd[IN]);
}

 //ok
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