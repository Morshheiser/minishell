#include "../../../include/minishell.h"

char *ft_strjoin_free(char *s1, char *s2)
{
    char *joined_str;

    // Depuração: Exibindo as strings antes da junção
    printf("Juntando strings: '%s' e '%s'\n", s1, s2);

    joined_str = ft_check_alloc(ft_strjoin(s1, s2), "expansion");

    // Depuração: Exibindo o resultado da junção
    printf("Resultado da junção: '%s'\n", joined_str);

    free(s1);
    free(s2);
    return joined_str;
}

char *ft_merge_strings(char *s1, char *s2)
{
    // Depuração: Exibindo as entradas
    printf("Merge strings: s1='%s', s2='%s'\n", s1, s2);

    if (s2 == NULL)
    {
        free(s1);
        // Depuração: s2 é NULL, retornando NULL
        printf("s2 é NULL, retornando NULL\n");
        return NULL;
    }
    if (s1 == NULL)
        return ft_strdup(s2);
    return ft_strjoin_free(s1, s2);
}

int ft_isolate(char **src, char **var)
{
    int i = 2;
    int ret = 1;
    char *line;

    line = *src;

    // Depuração: Exibindo o início do processamento
    printf("Isolando variável a partir de: '%s'\n", line);

    while (line[i] && line[i] != '}')
    {
        if (!ft_isalnum(line[i]) && line[i] != '_')
            ret = 0;
        i++;
    }

    if (!line[i])
        ret = 0;

    *var = ft_check_alloc(ft_substr(line, 0, i + 1), "expansion");

    // Depuração: Exibindo a variável isolada
    printf("Variável isolada: '%s'\n", *var);

    *src = line + i;
    if (line[i])
        *src += 1;

    // Depuração: Exibindo o ponteiro src após o processamento
    printf("Ponteiro src após isolamento: '%s'\n", *src);

    return ret;
}
