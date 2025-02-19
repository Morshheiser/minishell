#include "../../include/minishell.h"

int ft_isolate(char **input, char **extracted_var)
{
    int index;
    int is_valid;
    char *line;

    index = 2;
    is_valid = 1;
    line = *input;
    while (line[index] && line[index] != '}')
    {
        if (!ft_isalnum(line[index]) && line[index] != '_')
            is_valid = 0;
        index++;
    }
    if (!line[index])
        is_valid = 0;
    *extracted_var = ft_check_alloc(ft_substr(line, 0, index + 1), "expansion");
    *input = line + index;
    if (**input)
        *input += 1;
    return is_valid;
}
