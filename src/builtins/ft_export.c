#include "../../include/minishell.h"



void free_split(char **split)
{
    int i;

    i = 0;
    if (!split)
        return;
    while (split[i])
        free(split[i++]);
    free(split);
}

int ft_check_arg(const char *arg)
{
    int i;

    i = 0;
    if (ft_isalpha(arg[i]) || arg[i] == '_')
    {
        while (ft_isalnum(arg[i]) || arg[i] == '_')
            i++;
        if (arg[i] == '=')
            return 0;
        if (arg[i] == '\0')
            return 1;
    }
    printf("export: `%s': not a valid identifier\n", arg);
    status_g = 1;
    return (status_g);
}

// Lista todas as variáveis de ambiente
void ft_list_env(t_env *env)
{
    char **temp;
    int i;

    if (!env || !env->var_list)
        return;
    i = -1;
    while (env->var_list[++i])
    {
        temp = ft_split(env->var_list[i], '=');
        if (temp[0] && temp[1])
            printf("declare -x %s=\"%s\"\n", temp[0], temp[1]);
        else
            printf("declare -x %s\n", temp[0]);
        ft_free_arr(temp);
    }
}


// Adiciona uma nova variável de ambiente ou atualiza se já existir
int ft_update_or_add_var(t_env *env, char *arg)
{
    char    **split;
    char    **new_env;
    int     index;

    split = ft_split(arg, '=');
    index = ft_srch_arr(env->var_list, split[0]);
    ft_free_arr(split);
    if (index != -1)
    {
        free(env->var_list[index]);
        env->var_list[index] = ft_strdup(arg);
    }
    else
    {
        new_env = ft_arr_copy(env->var_list, 1);
        new_env[ft_size_arr(env->var_list)] = ft_strdup(arg);
        ft_free_arr(env->var_list);
        env->var_list = new_env;
    }
    return 0;
}

// Função principal para exportar variáveis
int ft_export(char **args, t_env *env)
{
    int i;

    status_g = 0;
    if (args[0] && args[1] == NULL)
        ft_list_env(env);
    {
        i = 1;
        while(args[i])
        {
            if (!ft_check_arg(args[i]))
                ft_update_or_add_var(env, args[i]);
            i++;
        }
    }
}
