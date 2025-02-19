#include "../../include/minishell.h"

void	*ft_check_alloc(void *str, char *text)
{
	if (str == NULL)
	{
		errno = ENOMEM;
		ft_perror(0, text, 0);
	}
	return (str);
}