#include "../../../include/minishell.h"

char	*ft_find_exit_status(char **line, int i)
{
    char	*ret;

    // Debug: Exibindo o valor do status
    printf("Chamando ft_find_exit_status com status: %d\n", i);

    ret = ft_itoa(i);  // Converte o código de status em string
    *line += 2;  // Avança o ponteiro de linha para além do '$?'
    
    // Debug: Mostrando o valor convertido para string
    printf("Status convertido: '%s'\n", ret);

    return (ret);
}

char	*ft_get_env_in_brackets(char **line, char **envp)
{
    char	*env;
    char	*temp;
    int		ret;

    // Debug: Exibindo a linha atual
    printf("Chamando ft_get_env_in_brackets com linha: '%s'\n", *line);
    (void) envp;
    ret = ft_isolate(line, &temp);  // Separa a variável entre as chaves
    if (!ret)
    {
        free(temp);
        ft_perror(0, temp, "not substitution");
        
        // Debug: Mensagem de erro caso a variável não seja isolada
        printf("Erro ao isolar variável no formato ${VAR}\n");

        return (0);
    }
    env = ft_strtrim(temp, "${}");  // Remove as chaves
    free(temp);
    
    // Debug: Exibindo a variável sem as chaves
    printf("Variável isolada: '%s'\n", env);

    temp = ft_find_env_value(env, envp);  // Busca o valor da variável no ambiente
    free(env);

    // Debug: Exibindo o valor da variável encontrada
    printf("Valor da variável: '%s'\n", temp);

    return (temp);
}


char *ft_get_arg_value(char **line, char **argv)
{
    int index = 0;
    int target_index;
    char *result;
    char *index_str;

    result = 0;
    *line += 1;  // Avança para o índice após o '$'
    index_str = ft_substr(*line, 0, 1);  // Extrai o índice como string
    if (!index_str)
        return (NULL);

    // Debug: Exibindo o índice extraído
    printf("Índice extraído: '%s'\n", index_str);

    target_index = atoi(index_str);  // Converte o índice para inteiro
    // Debug: Exibindo o índice alvo
    printf("Índice alvo: %d\n", target_index);
    while ((*argv)[index])
    {
        if (index == target_index)
        {
            result = ft_strdup(argv[index]);  // Obtém o argumento correspondente
            break;
        }
        index++;
    }
    *line += 1;

    // Debug: Exibindo o valor do argumento obtido
    if (result)
        printf("Valor do argumento: '%s'\n", result);
    else
        printf("Argumento não encontrado\n");
    free(index_str);
    return (result);
}


char	*ft_get_env_variable(char **line, char **env)
{
    int		i;
    char	*key;
    char	*value;

    i = 0;
    *line += 1;  // Avança para o início da variável após o '$'
    while ((*line)[i] && (ft_isalnum((*line)[i]) || (*line)[i] == '_'))
        i++;
    
    // Debug: Exibindo a chave extraída
    key = ft_substr(*line, 0, i);
    if (!key)
        return (NULL);
    printf("Chave extraída: '%s'\n", key);

    value = ft_find_env_value(key, env);  // Busca o valor da variável
    *line += i;  // Avança o ponteiro da linha
    free(key);

    // Debug: Exibindo o valor da variável
    printf("Valor da variável: '%s'\n", value);

    return (value);
}

char *ft_expand_env_variable(char **input, char **args, char **env)
{
    char *result;
    char next_char;

    result = NULL;
    next_char = *(*input + 1);
    if (next_char == '?')
        result = ft_find_exit_status(input, status_g);
    else if (next_char == '{')
        result = ft_get_env_in_brackets(input, env);
    else if (ft_isdigit(next_char))
        result = ft_get_arg_value(input, args);
    else if (ft_isalpha(next_char) || next_char == '_')
            result = ft_get_env_variable(input, env);
    else
    {
        result = ft_strdup("$");
        *input += 1;
    }
    printf("Resultado da expansão: '%s'\n", result);
    return result;
}



