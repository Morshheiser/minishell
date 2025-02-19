#include "../../include/minishell.h"

char **ft_split_with_set(char *line, const char *set)
{
    char **split;
    int i = 0;
    int len;
    int num_words;

    if (!line || !set)
    {
        return (0);
    }

    split = ft_allocate_split(line, set);
    if (!split)
    {
        return NULL;
    }

    num_words = ft_count_word(line, set);

    while (i < num_words)
    {
        while (ft_strchr(set, *line))
            line++;

        len = ft_len_word(line, set);

        split[i] = ft_sub_word(line, len);
        if (!split[i])
        {
            return (ft_free_splterr(split));
        }

        line += len;
        i++;
    }

    split[i] = NULL;

    return split;
}


char **ft_allocate_split(char *line, const char *set)
{
    char **split;
    int words;

    if (!line || !set)
        return NULL;
    words = ft_count_word(line, set);
    split = ft_calloc(words + 1, sizeof(char *));
    return split;
}

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

