
#include "../../include/minishell.h"

void    ft_initialize_env(t_env **env, char **env_array)
{
    char    *pwd;
    int     i;
    int     len;

    (*env) = malloc(sizeof(t_env));
    if (!(*env))
        return ;
    (*env)->var_list = ft_arr_copy(env_array, 0);
    pwd = NULL;
    len = ft_strlen("PWD");
    i = -1;
    while ((*env)->var_list[++i])
    {
        if (ft_strncmp((*env)->var_list[i], "PWD", len) == 0
         && (*env)->var_list[i][len] == '=')
        {
            pwd = (*env)->var_list[i];
            break;
        }
    }
    if (pwd)
        (*env)->pwd = ft_strdup(pwd + 4);
    else
        (*env)->pwd = getcwd(NULL, 0);
}
