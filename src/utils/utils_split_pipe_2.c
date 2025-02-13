#include "../../include/minishell.h"

int ft_count_word(char *line, const char *set)
{
    int words = 0;
    int aux;
    int i = 0;

    if (!line || !set)
        return (0);

    while (line[i])
    {
        if (line[i] && !ft_strchr(set, line[i]))
        {
            words++;
            while (line[i] && !ft_strchr(set, line[i]))
            {
                aux = ft_find_quote_end(&line[i]);
                if (aux)
                    i += aux;
                else
                    i++;
            }
        while (line[i] && ft_strchr(set, line[i]))
            i++;
        }
    }
    return (words);
}

int ft_len_word(char *line, const char *set)
{
    int i;
    int quote_len;

    if (!line || !set)
        return (0);
    i = 0;
    while (line[i] && !ft_strchr(set, line[i]))
    {
        quote_len = ft_find_quote_end(&line[i]);
        if (quote_len) 
            i = i + quote_len;
        else
            i++;
    }
    return (i);
}

 char *ft_sub_word(char *line, int len)
{
    char *word;
    char *temp;

    if (!line)
        return (0);
    temp = ft_substr(line, 0, len);
    word = ft_strtrim(temp, " \t\n\v\f\r");
    free(temp);
    return (ft_check_alloc(word, "split"));
}

char **ft_free_splterr(char **split)
{
    int i;

    if (!split)
        return (0);
    i = 0;
    while (*(split)[i])
    {
        free(split[i]);
        i++;
    }
    return (0);
}
