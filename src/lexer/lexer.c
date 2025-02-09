#include "../../include/minishell.h"

int ft_check_closed_op(char *str)
{
    char quote_type;
    int i;

    i = 0;
    printf("[DEBUG] Iniciando ft_check_closed_op com a string: %s\n", str);
    while (str[i])
    {
        printf("[DEBUG] Analisando caractere: %c (posição %d)\n", str[i], i);
        if ((str[i] == '\'') || (str[i] == '\"'))
        {
            quote_type = str[i++];
            printf("[DEBUG] Aspas encontradas: %c\n", quote_type);
            while (str[i] && (str[i] != quote_type))
                i++;
            if (!str[i])
            {
                printf("[DEBUG] Erro: aspas desbalanceadas\n");
                return (ft_lex_error(str[i], 1));
            }
        }
        i++;
    }
    printf("[DEBUG] ft_check_closed_op passou com sucesso\n");
    return (1);
}

int ft_check_pipe_syntax(char *str)
{
    int arg;
    int i;

    arg = 0;
    i = 0;
    printf("[DEBUG] Iniciando ft_check_pipe_syntax com a string: %s\n", str);
    while (str[i])
    {
        printf("[DEBUG] Analisando caractere: %c (posição %d)\n", str[i], i);
        i += ft_find_quote_end(&str[i]);
        if (!str[i])
        {
            printf("[DEBUG] Erro: pipe com sintaxe inválida (fim de string)\n");
            return (ft_lex_error(str[i], 2));
        }
        if (!arg && (!ft_isspace(str[i]) && (str[i] != '|')))
        {
            arg = '|';
            printf("[DEBUG] Pipe encontrado, marcando arg como '|'\n");
        }
        if (str[i] == '|')
        {
            if (!arg)
            {
                printf("[DEBUG] Erro: pipe encontrado antes de um argumento\n");
                return (ft_lex_error(str[i], 3));
            }
            arg -= str[i];
        }
        i++;
    }
    if (!arg)
    {
        printf("[DEBUG] Erro: pipe no final sem argumento\n");
        return (ft_lex_error(str[i], 4));
    }
    printf("[DEBUG] ft_check_pipe_syntax passou com sucesso\n");
    return (arg);
}

int ft_check_redir_syntax(char *str, char opt)
{
    int redir;
    int i;

    i = 0;
    printf("[DEBUG] Iniciando ft_check_redir_syntax com a string: %s e operador: %c\n", str, opt);
    while (str[i] != '\0')
    {
        redir = 0;
        if (str[i] == '\'' || str[i] == '\"')
            i += ft_find_quote_end(&str[i]) + 1;
        else if (str[i] == opt)
        {
            printf("[DEBUG] Encontrado operador de redirecionamento: %c\n", opt);
            while (str[i + redir] == opt && redir < 4)
                redir++;
            if (redir > 2)
            {
                printf("[DEBUG] Erro: excesso de operadores de redirecionamento\n");
                return (ft_lex_error(str[i], 5));
            }
            i += redir;
            while (ft_isspace(str[i]))
                i++;
            if (str[i] == '\0' || str[i] == '|' || str[i] == '>' || str[i] == '<')
            {
                printf("[DEBUG] Erro: falta de argumento após redirecionamento\n");
                return (ft_lex_error(str[i], 6));
            }
        }
        i++;
    }
    printf("[DEBUG] ft_check_redir_syntax passou com sucesso\n");
    return (1);
}

int ft_lex_error(char c, int n)
{
    printf("[DEBUG] Erro detectado, código: %d, caractere: %c\n", n, c);
    
    if (!c)
        status_g = ft_perror(2, "lexer", "erro de sintaxe: token inesperado 'newline' encontrado");
    else if (c == '|')
        status_g = ft_perror(2, "lexer", "erro de sintaxe: uso incorreto do operador pipe '|'");
    else if (c == '<' || c == '>')
        status_g = ft_perror(2, "lexer", "erro de sintaxe: redirecionamento inválido '%c'", c);
    else if (ft_isspace(c))
        status_g = ft_perror(2, "lexer", "erro de sintaxe: espaço extra não esperado antes do token");
    else
        status_g = ft_perror(2, "lexer", "erro de sintaxe: operador inválido '%c' encontrado", c);
    
    return (0);
}

int ft_isspace(char c)
{
    printf("[DEBUG] Verificando se o caractere '%c' é um espaço\n", c);
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

int ft_str_is_space(const char *str)
{
    printf("[DEBUG] Verificando se a string '%s' é composta apenas por espaços\n", str);
    if (!str)
        return (1);
    while (*str)
    {
        if (!ft_isspace(*str))
            return (0);
        str++;
    }
    return (1);
}
