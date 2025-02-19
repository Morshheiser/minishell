#include "../../include/minishell.h"

void ft_free_arr(char **arr)
{
    int i;

    if (!arr)
        return;
    i = -1;
    while (arr[++i])
        free(arr[i]);
    free(arr);
}

void ft_free_env(t_env *env)
{
    int i;
    
    i = 0;
    if (!env || !env->var_list)
        return;
    while (env->var_list[i])
     {
        free(env->var_list[i]);
        i++;
    }
    if (env->var_list)
        free(env->var_list);
    if (env->pwd)
        free(env->pwd);
}
