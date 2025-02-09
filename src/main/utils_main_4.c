#include "../../include/minishell.h"


t_shell start_function(char **argv, char **env)
{
    t_shell shell;
    
    ft_memset(&shell, 0, sizeof(t_shell));
    shell.argv = argv;
    shell.fd[0] = dup(STDIN_FILENO);
    shell.fd[1] = dup(STDOUT_FILENO);
    shell.env = malloc(sizeof(t_env));
    if (!shell.env)
        exit(EXIT_FAILURE);
    ft_init_env(&shell.env, env);
    return (shell);
}


void	ft_setsignal(void)
{
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, ft_error_handler_sigint);
}

static void	ft_error_handler_sigint(int sig)
{
	if (sig == SIGINT)
	{
		status_g = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	while (s1[i] && i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}
