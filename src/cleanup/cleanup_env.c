#include "../../include/minishell.h"

void ft_cleanup_env(t_env *env)
{
    int i;
    
    i = 0;
    if (env->var_list)
    {
        while (env->var_list[i])
        {
            free(env->var_list[i]);
            i++;
        }

            free(env->var_list);
    }
    if (env->pwd)
        free(env->pwd);
}