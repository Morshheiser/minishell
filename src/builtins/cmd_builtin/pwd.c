#include "../../../include/minishell.h"

void ft_pwd(char **args, t_env *env)
{
    (void)args;

    status_g = 0;
    if (!env)
    {
        status_g = 1;
        return;
    }
    if (env->pwd)
        printf("%s\n", env->pwd);
    else
    {
        free(env->pwd);
        env->pwd = getcwd(NULL, 0);
        if(env->pwd)
            printf("%s\n", env->pwd);
        else
            status_g = 1;
    }
}