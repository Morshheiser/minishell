#include "../../include/minishell.h"

int ft_size(char **arr)
{
    int len;

    len = 0;
    if (!arr)
        return (len);
    while (arr[len])
        len++;
    return (len);
}

int ft_vetor_size(char **ev)
{
    int i;

    i = 0;
    while (ev[i])
        i++;
    return i;
}

int	ft_size_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}