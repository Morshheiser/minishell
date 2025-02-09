#include "../../include/minishell.h"

int ft_vetor_size(char **ev)
{
    int i = 0;
    while (ev[i])
        i++;
    return i;
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
    while(++i < list_size)
        new_list[i] = env->var_list[i];
    new_list[list_size] = ft_strjoin(key, "=");
    new_list[list_size] = ft_strjoin(new_list[list_size], value);
    new_list[list_size + 1] = NULL;
    free(env->var_list);
    env->var_list = new_list;
}


void ft_free_env(t_env *env)
{
    int i = 0;
    while (env->var_list && env->var_list[i])
    {
        free(env->var_list[i]);
        i++;
    }
    free(env->var_list);
    free(env->pwd);
}
