#include "../../include/minishell.h"

char **ft_arr_copy(char **arr, int size)
{
    int i;
    int len;
    char **arr_cpy;

    if (!arr)
        return (NULL);
    i = 0;
    len = 0;
    while (arr[len])
        len++;
    arr_cpy = malloc(sizeof(char *) * (len + 1 + size));
    ft_memset(arr_cpy, 0, sizeof(char *) * (len + 1 + size));
    if (!arr_cpy)
        return (NULL);
    while (i < len && arr[i])
    {
        arr_cpy[i] = ft_strdup(arr[i]);
        i++;
    }
    while (i < len + size)
    {
        arr_cpy[i] = NULL;
        i++;
    }
    return (arr_cpy);
}
