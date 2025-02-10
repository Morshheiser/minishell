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
/*
// Função para expandir o conteúdo dentro das aspas duplas
char *ft_expand_within_quotes(char **input, char **args, char **env)
{
    char    *str = 0;
    char    *line_tmp = NULL;

   	while (*(*input) && (*(*input) != '\"'))
	{
		if (*(*input) == '$')
			line_tmp = ft_expand_env_variable(input, args, env);
		else
			line_tmp = ft_expand_plain_text(input, "$\"");
        str = ft_merge_strings(str, line_tmp);
	}
   return (str);
}

// Função para expandir as aspas duplas
char *ft_expand_double_quotes(char **input, char **args, char **env)
{
    char *result;

    if (!ft_check_double_quote_syntax(*input))
        return 0;
    *input = *input + 1;
    result = ft_expand_within_quotes(input, args, env);
    if (*(*input))
		*(input)++;
    if (!result || !*result) 
    {
        free(result);
        result = ft_calloc(1, 1);
    }
    printf("Resultado final após expansão de aspas duplas: '%s'\n", result);
    return result;
}*/

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

    // Debug: Verificando linha antes de prosseguir
    printf("Iniciando expansão de aspas simples. Linha inicial: '%s'\n", current_line);

    if (*current_line)
        current_line++;

    // Procurando pelo fechamento das aspas simples
    while (current_line[i] && current_line[i] != '\'')
        i++;

    // Se não encontrar a aspa simples de fechamento
    if (!current_line[i])
    {
        // Debug: Erro de sintaxe para aspas simples desbalanceadas
        printf("Erro de sintaxe: aspas simples desbalanceadas. Posição final: %d\n", i);
        ft_perror(0, "syntax_error", "mismatched single quote");
        return (0);
    }

    // Extraindo a string entre as aspas simples
    str = ft_substr(current_line, 0, i);

    if (!str || !*str)
    {
        free(str);
        str = ft_calloc(1, 1);
    }

    *line = current_line + i + 1;

    // Debug: Exibindo a string extraída
    printf("Valor extraído de aspas simples: '%s'\n", str);

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

    // Debug: Iniciando a extração de texto simples
    printf("Iniciando extração de texto simples a partir de: '%s'\n", start);

    // Percorrendo a string para encontrar os caracteres de fim de expansão
    while (*current_char && !ft_strchr(eofs, *current_char))
        current_char++;

    // Extraindo a parte da string
    str = ft_substr(start, 0, current_char - start);

    *line = current_char;

    // Debug: Exibindo o texto extraído
    printf("Texto extraído: '%s'\n", str);

    return (str);
}
