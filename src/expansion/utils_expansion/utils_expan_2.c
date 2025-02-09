#include "../../../include/minishell.h"

// Função para verificar a sintaxe das aspas duplas
int ft_check_double_quote_syntax(char *str)
{
    int i = 0;
    int quote_count = 0;

    printf("Iniciando a verificação de sintaxe das aspas duplas para a string: %s\n", str);

    // Verificando as aspas duplas
    while (str[i]) {
        if (str[i] == '\"') {
            quote_count++;
        }
        i++;
    }

    printf("Número de aspas duplas encontradas: %d\n", quote_count);

    // Verificando se as aspas duplas estão balanceadas
    if (quote_count % 2 != 0) {
        printf("Erro de sintaxe: aspas duplas desbalanceadas.\n");
        ft_perror(0, "syntax_error", "mismatched double quotes");
        return 0;
    }

    printf("Aspas duplas balanceadas.\n");
    return 1;
}

// Função para expandir o conteúdo dentro das aspas duplas
int ft_expand_within_quotes(char *line, char **result, char **args, char **env)
{
    int i = 0;
    char *temp;

    printf("Iniciando a expansão dentro das aspas: '%s'\n", line);

    while (line[i] && line[i] != '\"') {
        printf("Analisando caractere '%c' na posição %d\n", line[i], i); 

        // Se encontrar o sinal de dólar para variável
        if (line[i] == '$') {
            printf("Detectado '$' na posição %d. Iniciando expansão de variável...\n", i);
            temp = ft_expand_env_variable(&line, args, env);
        }
        // Caso contrário, tratar como texto simples
        else {
            printf("Texto simples detectado. Iniciando expansão...\n");
            temp = ft_expand_plain_text(&line, "$\"");
        }

        printf("Concatenando com o resultado. Resultado parcial: '%s'\n", *result);
        *result = ft_merge_strings(*result, temp);
        i++;
    }

    printf("Resultado final após expansão dentro das aspas: '%s'\n", *result);
    return i;
}

// Função para expandir as aspas duplas
char *ft_expand_double_quotes(char **input, char **args, char **env)
{
    char *result = NULL;
    char *line = *input;
    int i;

    printf("Iniciando expansão de aspas duplas. Linha inicial: '%s'\n", line);

    // Avançando para após a primeira aspa dupla
   // line++;

    // Verificando a sintaxe das aspas duplas
    printf("Verificando a sintaxe das aspas duplas...\n");
    if (!ft_check_double_quote_syntax(line)) {
        printf("Erro de sintaxe nas aspas duplas. Saindo da função.\n");
        return NULL;
    }

    printf("Sintaxe das aspas duplas está correta, iniciando expansão...\n");

    i = ft_expand_within_quotes(line, &result, args, env);

    *input = line + i;

    if (!result || !*result) {
        printf("Resultado vazio ou NULL após expansão, alocando espaço vazio\n");
        free(result);
        result = ft_calloc(1, 1);
    }

    printf("Resultado final após expansão de aspas duplas: '%s'\n", result);

    return result;
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
