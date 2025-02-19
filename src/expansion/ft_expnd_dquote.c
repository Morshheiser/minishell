#include "../../include/minishell.h"

char *ft_expand_double_quotes(char **input, char **argv, char **env)
{    
    char *str;
    char *tmp;

    str = 0;

    if (!ft_check_double_quote_syntax(*input))
        return (0);
    *input += 1;
    while (*(*input) && (*(*input) != '\"'))
    {
        if (*(*input) == '$')
            tmp = ft_expand_env_variable(input, argv, env);
        else
            tmp = ft_expand_plain_text(input, "$\"");
        str = ft_merge_strings(str, tmp);
    }
    if (*(*input))
        *input += 1;
    if (!str || !*str)
    {
        free(str);
        str = ft_calloc(1, 1);
    }
    return (str);
}


//ok
int ft_check_double_quote_syntax(char *str)
{
    int i;
    int quote_count;

    i = 0;
    quote_count = 0;
    while (str[i])
    {
        if (str[i] == '\"')
            quote_count++;
        i++;
    }
    if (quote_count % 2 != 0)
    {
        ft_perror(0, "syntax_error", "aspas duplas desbalanceadas.");
        return 0;
    }
    return 1;
}
