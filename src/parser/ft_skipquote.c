#include "../../include/minishell.h"
//ok
int	ft_find_quote_end(char *str)
{
	int		i;
	char	quote_char;

	if (!str)
		return (0);
	i = 0;
	quote_char = str[i];
	if (str[i] == '\'' || str[i] == '\"')
	{
        i++;
		while (str[i] && str[i] != quote_char)
			i++;
		if (str[i] == quote_char)
			return (i);
	}
	return (0);
}