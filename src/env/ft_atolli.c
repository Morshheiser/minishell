
#include "../../include/minishell.h"

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
