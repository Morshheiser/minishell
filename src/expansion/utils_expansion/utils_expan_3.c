#include "../../../include/minishell.h"


char *ft_merge_strings(char *s1, char *s2)
{
    char *joined_str;

    if (s2 == NULL)
    {
        free(s1);
        return NULL;
    }
    joined_str = ft_check_alloc(ft_strjoin(s1, s2), "expansion");
    if (!joined_str)
    {
        free(s1);
        free(s2);
        return NULL;
    }
    free(s1);
    free(s2);
    return joined_str;
}

int ft_isolate(char **src, char **var)
{
    int i = 2;
    int ret = 1;
    char *line;

    line = *src;
    while (line[i] && line[i] != '}')
    {
        if (!ft_isalnum(line[i]) && line[i] != '_')
            ret = 0;
        i++;
    }
    if (!line[i])
        ret = 0;
    *var = ft_check_alloc(ft_substr(line, 0, i + 1), "expansion");
    *src = line + i;
    if (line[i])
        *src += 1;
    return ret;
}
