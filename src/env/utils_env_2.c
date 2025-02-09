#include "../../include/minishell.h"

char *ft_find_env(char *key, char **env)
{
    int i;
    int key_len;

    printf("[DEBUG] Iniciando busca pela chave '%s' no ambiente...\n", key);

    if (!key || !env)
    {
        printf("[DEBUG] Chave ou ambiente inválido.\n");
        return (NULL);
    }
    
    key_len = ft_strlen(key);
    i = 0;

    while (env[i])
    {
        printf("[DEBUG] Comparando '%s' com '%s'...\n", key, env[i]);

        if (ft_strncmp(key, env[i], key_len) == 0 && env[i][key_len] == '=')
        {
            printf("[DEBUG] Chave '%s' encontrada: '%s'\n", key, env[i]);
            return (env[i]);
        }
        i++;
    }

    printf("[DEBUG] Chave '%s' não encontrada no ambiente.\n", key);
    return (NULL);
}

char *ft_find_env_value(char *key, char **env)
{
    char *var;

    printf("[DEBUG] Buscando valor para a chave '%s'...\n", key);

    var = ft_find_env(key, env);
    if (var)
    {
        printf("[DEBUG] Valor encontrado: '%s'\n", var);
        return (ft_strdup(ft_strchr(var, '=') + 1));  // Retorna o valor após o '='
    }

    printf("[DEBUG] Valor não encontrado para a chave '%s'.\n", key);
    return (NULL);
}

void ft_init_env(t_env **env, char **envp)
{
    printf("[DEBUG] Inicializando o ambiente...\n");

    *env = malloc(sizeof(t_env));
    if (!*env)
    {
        printf("[DEBUG] Falha ao alocar memória para o ambiente.\n");
        return;
    }

    printf("[DEBUG] Copiando variáveis de ambiente...\n");
    (*env)->var_list = ft_arr_copy(envp, 0);
    printf("[DEBUG] Buscando o valor de 'PWD'...\n");
    (*env)->pwd = ft_find_env_value("PWD", (*env)->var_list);

    if (!(*env)->pwd)
    {
        printf("[DEBUG] Não encontrado 'PWD' no ambiente, utilizando getcwd.\n");
        (*env)->pwd = getcwd(NULL, 0);
    }
    else
    {
        printf("[DEBUG] PWD encontrado: '%s'\n", (*env)->pwd);
    }
}

void ft_free_arr(char **arr)
{
    int i;

    if (!arr)
    {
        printf("[DEBUG] Nenhum array para liberar.\n");
        return;
    }

    printf("[DEBUG] Liberando array...\n");
    i = -1;
    while (arr[++i])
    {
        printf("[DEBUG] Liberando '%s'...\n", arr[i]);
        free(arr[i]);
    }
    free(arr);
    printf("[DEBUG] Array liberado.\n");
}
