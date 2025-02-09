#include "../../include/minishell.h"
#include "../../include/minishell.h"

int ft_vetor_size(char **ev)
{
    int i = 0;
    printf("[DEBUG] Calculando o tamanho do vetor...\n");
    while (ev[i])
        i++;
    printf("[DEBUG] Tamanho do vetor: %d\n", i);
    return i;
}

void ft_env_addback(t_env *env, char *key, char *value)
{
    int i;
    int list_size;
    char **new_list;

    if (!env || !key || !value) {
        printf("[DEBUG] Parâmetros inválidos na função ft_env_addback.\n");
        return;
    }

    list_size = ft_vetor_size(env->var_list);
    printf("[DEBUG] Tamanho da lista de variáveis de ambiente: %d\n", list_size);
    
    new_list = malloc(sizeof(char *) * (list_size + 2));
    if (!new_list) {
        printf("[DEBUG] Erro ao alocar memória para nova lista.\n");
        return;
    }

    printf("[DEBUG] Alocação de nova lista bem-sucedida.\n");

    i = -1;
    while (++i < list_size) {
        printf("[DEBUG] Copiando variável de ambiente: %s\n", env->var_list[i]);
        new_list[i] = env->var_list[i];
    }

    // Concatenando key e value
    new_list[list_size] = ft_strjoin(key, "=");
    printf("[DEBUG] String concatenada (key + '='): %s\n", new_list[list_size]);

    new_list[list_size] = ft_strjoin(new_list[list_size], value);
    printf("[DEBUG] String final (key + '=' + value): %s\n", new_list[list_size]);

    new_list[list_size + 1] = NULL;
    printf("[DEBUG] Adicionando NULL ao final da nova lista.\n");

    free(env->var_list);
    env->var_list = new_list;

    printf("[DEBUG] Variável de ambiente adicionada com sucesso!\n");
}

void ft_free_env(t_env *env)
{
    int i = 0;
    if (!env || !env->var_list) {
        printf("[DEBUG] Nenhuma variável de ambiente para liberar.\n");
        return;
    }

    printf("[DEBUG] Liberando variáveis de ambiente...\n");

    while (env->var_list && env->var_list[i]) {
        printf("[DEBUG] Liberando variável de ambiente: %s\n", env->var_list[i]);
        free(env->var_list[i]);
        i++;
    }
    free(env->var_list);

    if (env->pwd) {
        printf("[DEBUG] Liberando pwd: %s\n", env->pwd);
        free(env->pwd);
    }

    printf("[DEBUG] Variáveis de ambiente liberadas com sucesso!\n");
}
