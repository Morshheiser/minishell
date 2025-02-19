#include "../../include/minishell.h"

char *ft_expand_plain_text(char **line, char *eofs)
{
    int i;
    char *result;
    char *current_char;

    if (!line)
        return (0);
    i = 0;
    current_char = *line;
    while (current_char[i])
    {
        if (!ft_strchr(eofs, current_char[i]))
            i++;
        else
            break;
    }
    result = ft_substr(current_char, 0, i);
    *line += i;
    return (result);
}
