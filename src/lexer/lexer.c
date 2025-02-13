#include "../../include/minishell.h"

int ft_check_closed_op(char *str)
{
    char quote_type;
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] == '\'') || (str[i] == '\"'))
        {
            quote_type = str[i];
            i++;
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
    return (1);
}

int ft_check_pipe_syntax(char *str)
{
    int arg;
    int i;

    arg = 0;
    i = 0;
    while (str[i])
    {
        i += ft_find_quote_end(&str[i]);
        if (!str[i])
            return (ft_lex_error(str[i], 2));
        if (!arg && (!ft_isspace(str[i]) && (str[i] != '|')))
            arg = '|';
        if (str[i] == '|')
        {
            if (!arg)
                return (ft_lex_error(str[i], 3));
            arg -= str[i];
        }
        i++;
    }
    if (!arg)
        return (ft_lex_error(str[i], 4));
    return (arg);
}

int ft_check_redir_syntax(char *str, char opt)
{
    int redir;
    int i;
    int num;

    num = ft_strlen(str);
    i = 0;
    while (str[i] && i < num)
    {
        redir = 0;
        if (str[i] == '\'' || str[i] == '\"')
            i += ft_find_quote_end(&str[i]) + 1;
        else if (str[i] == opt)
        {
            while (str[i + redir] == opt && redir < 4 && i + redir < num)
                redir++;
            if (redir > 2)
                return (ft_lex_error(str[i], 5));
            i += redir;
            while (ft_isspace(str[i]))
                i++;
            if (str[i] == '\0' || str[i] == '|' || str[i] == '>' || str[i] == '<')
                return (ft_lex_error(str[i], 6));
        }
        i++;
    }
    return (1);
}


int ft_lex_error(char c, int n)
{

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
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

int ft_str_is_space(const char *str)
{
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
