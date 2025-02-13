#include "../../../include/minishell.h"

// Função para verificar a sintaxe das aspas duplas
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

char *ft_expand_double_quotes(char **input, char **argv, char **env)
{
	char	*str;
	char	*tmp;

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
		free (str);
		str = ft_calloc(1, 1);
	}
	return (str);
}

char *ft_expand_single_quotes(char **line)
{
    char *str;
    int i;
    char *current_line;

    i = 0;
    current_line = *line;
    if (*current_line)
        current_line++;
    while (current_line[i] && current_line[i] != '\'')
        i++;
    if (!current_line[i])
    {
        ft_perror(0, "syntax_error", " aspas simples desbalanceadas. Posição final");
        return (0);
    }
    str = ft_substr(current_line, 0, i);
    if (!str || !*str)
    {
        free(str);
        str = ft_calloc(1, 1);
    }
    *line = current_line + i + 1;
    return (str);
}
char *ft_expand_plain_text(char **line, char *eofs)
{
    char *start;
    char *str;
    char *current_char;

    if (!line || !*line)
        return (0);
    start = *line;
    current_char = start;
    while (*current_char && !ft_strchr(eofs, *current_char))
        current_char++;
    str = ft_substr(start, 0, current_char - start);
    *line = current_char;
    return (str);
}
