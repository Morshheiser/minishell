#include "../../include/minishell.h"

void ft_pwd(char **args, t_env *env)
{
    (void)args;
    status_g = 0;
    if (!env)
        return;
    if (!env->pwd)
    {
        free(env->pwd);
        env->pwd = getcwd(NULL, 0);
        if (env->pwd)
            printf("%s\n", env->pwd);
        else
        {
            status_g = 1;
            perror("getcwd");
        }
    }
    else
        printf("%s\n", env->pwd);
}