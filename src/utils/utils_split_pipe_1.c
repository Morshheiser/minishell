#include "../../include/minishell.h"

void change_flag(char c, int *single_flag, int *double_flag)
{

    if (c == '\'' && *double_flag == 0)
        *single_flag = !(*single_flag);
    else if (c == '\"' && *single_flag == 0)
        *double_flag = !(*double_flag);

}


int ft_count_pipe(char *str)
{
    int i;
    int count;
    int single_flag;
    int double_flag;

    i = -1;
    count = 0;
    single_flag = 0;
    double_flag = 0;
    while (str[++i])
    {
        change_flag(str[i], &single_flag, &double_flag);
        if ((str[i] == 124) && !single_flag && !double_flag)
            count++;
    }
    return (count);
}

int	ft_find_quote_end(char *str)
{
	int		len;
	char	quote_char;

	if (!str)
		return (0);
	len = 0;
	quote_char = str[len];
	if (quote_char == '\'' || quote_char == '\"')
	{
		len++;
		while (str[len] && str[len] != quote_char)
			len++;
		if (str[len] == quote_char)
			return (len);
	}
	return (0);
}
