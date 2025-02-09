#include "../../../include/minishell.h"

int status_g = 0;

void free_split(char **split)
{
    int i = 0;
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
    status_g = 1;
    return (status_g); 
}

// Lista todas as variáveis de ambiente
void ft_list_env(t_env *env)
{
    int i;
    
    i = 0;
    if (!env || !env->var_list)
        return;
    while (env->var_list[i])
    {
        printf("declare -x %s\n", env->var_list[i]);
        i++;
    }
}

// Atualiza uma variável de ambiente se já existir
int ft_update_env_var(t_env *env, char **split)
{
    int i;
    char *key;
    
    i = 0;
    while (env->var_list[i])
    {
        key = strtok(env->var_list[i], "=");
        if (ft_strcmp(key, split[0]) == 0)
        {
            free(env->var_list[i]);
            env->var_list[i] = ft_strjoin(split[0], "=");
            env->var_list[i] = ft_strjoin(env->var_list[i], split[1]);
            free_split(split);
            return EXIT_SUCCESS;
        }
        i++;
    }
    return EXIT_FAILURE;
}

// Adiciona uma nova variável de ambiente
int ft_update_or_add_var(t_env *env, char *arg)
{
    char **split;
    char **new_var_list;
    int i;
    int j;
    
    i = 0;
    split = ft_split(arg, '=');
    if (ft_update_env_var(env, split) == EXIT_SUCCESS)
        return EXIT_SUCCESS;
    while (env->var_list[i])
        i++;
    new_var_list = malloc(sizeof(char *) * (i + 2));
    if (!new_var_list)
    {
        free_split(split);
        return EXIT_FAILURE;
    }
    j = -1;
    while(++j < i)
        new_var_list[j] = env->var_list[j];
    new_var_list[i] = ft_strjoin(split[0], "=");
    new_var_list[i] = ft_strjoin(new_var_list[i], split[1]);
    new_var_list[i + 1] = NULL;
    free(env->var_list);
    env->var_list = new_var_list;
    free_split(split);
    return EXIT_SUCCESS;
}

// Função principal para exportar variáveis
int ft_export(char **args, t_env *env)
{
    int i;

     if (!args || !env)
        return EXIT_FAILURE;
    if (!args[0])
        ft_list_env(env);
        return EXIT_SUCCESS;
    i = 0;
    while(args[i])
    {
    if (!ft_check_arg(args[i]))
        return (ft_update_or_add_var(env, args[i]));
        i++;
    }
    return EXIT_FAILURE;
}
