#include "../../include/minishell.h"

int ft_vetor_size(char **ev)
{
    int i;

    i = 0;
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
    while (++i < list_size)
        new_list[i] = env->var_list[i];
    new_list[list_size] = ft_strjoin(key, "=");
    new_list[list_size] = ft_strjoin(new_list[list_size], value);
    new_list[list_size + 1] = NULL;
     free(env->var_list);
    env->var_list = new_list;
    printf("[DEBUG] Variável de ambiente adicionada com sucesso!\n");
}

void ft_free_env(t_env *env)
{
    int i;
    
    i = 0;
    if (!env || !env->var_list)
        return;
    while (env->var_list && env->var_list[i]) {
        free(env->var_list[i]);
        i++;
    }
    free(env->var_list);

    if (env->pwd)
        free(env->pwd);
    printf("[DEBUG] Variáveis de ambiente liberadas com sucesso!\n");
}

void    ft_initialize_env(t_env **env, char **env_array)
{
    char    *pwd;
    int     i;
    int     srch_len;

    (*env) = malloc(sizeof(t_env));
    if (!(*env))
        return ;
    (*env)->var_list = ft_arr_copy(env_array, 0);
    pwd = NULL;
    srch_len = ft_strlen("PWD");
    i = -1;
    while ((*env)->var_list[++i])
    {
        if (ft_strncmp((*env)->var_list[i], "PWD", srch_len) == 0
         && (*env)->var_list[i][srch_len] == '=')
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
