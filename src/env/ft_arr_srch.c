#include "../../include/minishell.h"

int ft_srch_arr(char **array, char *str)
{
    int i;
    int len;

    if (!array || !str)
        return (-1);
    len = ft_strlen(str);
    i = 0;
    while (array[i]) {
        if (!ft_strncmp(array[i], str, len) && array[i][len] == '=')
            return (i);
        i++;
    }
    return (-1);
}