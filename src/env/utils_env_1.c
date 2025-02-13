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

long long int ft_atolli(const char *str)
{
    long long int result;
    int sign;
    int i;

    i = 0;
    result = 0;
    sign = 1;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (str[i] == '-')
    {
        sign *= -1;
        i++;
    } 
    else if (str[i] == '+')
        i++;
    while (ft_isdigit(str[i]))
    {
        result *= 10;
        result += sign * (str[i] - '0');
        i++;
    }
    return (result);
}
