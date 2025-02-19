#include "../../include/minishell.h"

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

int ft_str_is_space(const char *str)
{
    if (!str)
        return (1);
    while (*str)
    {
        if (!ft_isspace(*str))
            return (0);
        str++;
    }
    return (1);
}

void ft_env_addback(t_env *env, char *key, char *value)
{
    int i;
    int list_size;
    char **new_list;

    if (!env || !key || !value)
        return;
    list_size = ft_vetor_size(env->var_list);
    new_list = malloc(sizeof(char *) * (list_size + 2));
    if (!new_list)
        return;
    i = -1;
    while (++i < list_size)
        new_list[i] = env->var_list[i];
    new_list[list_size] = ft_strjoin(key, "=");
    new_list[list_size] = ft_strjoin(new_list[list_size], value);
    new_list[list_size + 1] = NULL;
    if(env->var_list)
        free(env->var_list);
    env->var_list = new_list;
}







