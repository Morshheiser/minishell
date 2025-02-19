#include "../../include/minishell.h"

int	ft_perror(int ret, char *text, char *msg, ...)
{
	va_list	apt;
	int		i;

	ft_print_message("bash", text, msg);
	if (msg)
	{
		va_start(apt, msg);
		i = -1;
        while (msg[++i])
		{
			if (msg[i] == '%' && msg[i + 1] != '\0')
			{
				if (msg[i + 1] == 's')
					ft_putstr_fd(va_arg(apt, char *), 2);
				else if (msg[i + 1] == 'c')
					ft_putchar_fd((char)va_arg(apt, int), 2);
				i++;
			}
			else
				ft_putchar_fd(msg[i], 2);
		}
		ft_putchar_fd('\n', 2);
		va_end(apt);
	}
	else
		perror(text);
	return (ret);
}


void	ft_print_message(char *shell, char *text, char *msg)
{
	if (shell != NULL)
	{
		ft_putstr_fd(shell, 2);
        if (text && *text)
		{
			ft_putstr_fd(": ", 2);
			if (msg)
				ft_putstr_fd(text, 2);
		}
		if (msg && *msg)
			ft_putstr_fd(": ", 2); 
	}
}

