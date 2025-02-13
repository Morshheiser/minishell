#include "../../include/minishell.h"

void change_flag(char c, int *single_flag, int *double_flag)
{

    if (c == '\'' && *double_flag == 0)
        *single_flag = !(*single_flag);
    else if (c == '\"' && *single_flag == 0)
        *double_flag = !(*double_flag);

}


int ft_count_pipe(char *str)
{
    int i;
    int count;
    int single_flag;
    int double_flag;

    i = -1;
    count = 0;
    single_flag = 0;
    double_flag = 0;
    while (str[++i])
    {
        change_flag(str[i], &single_flag, &double_flag);
        if ((str[i] == 124) && !single_flag && !double_flag)
            count++;
    }
    return (count);
}

int	ft_find_quote_end(char *str)
{
	int		len;
	char	quote_char;

	if (!str)
		return (0);
	len = 0;
	quote_char = str[len];
	if (quote_char == '\'' || quote_char == '\"')
	{
		len++;
		while (str[len] && str[len] != quote_char)
			len++;
		if (str[len] == quote_char)
			return (len);
	}
	return (0);
}

char **ft_allocate_split(char *line, const char *set)
{
    char **split;
    int words;

    if (!line || !set)
        return NULL;
    words = ft_count_word(line, set);
    split = ft_calloc(words + 1, sizeof(char *));
    if (!split)
        return NULL;
    return split;
}

char **ft_split_pipe(char *line, const char *set)
{
    char **split;
    int i = 0;
    int len;
    int num_words;

    split = ft_allocate_split(line, set);
    if (!split)
        return NULL;
    num_words = ft_count_word(line, set);
    while (i < num_words)
    {
        while (ft_strchr(set, *line))
            line++;
        len = ft_len_word(line, set);
        split[i] = ft_sub_word(line, len);
        if (!*(split)[i])
            return (ft_free_splterr(split));
        line += len;
        i++;
    }
    split[i] = NULL;
    return split;
}



