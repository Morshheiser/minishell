#include "../../include/minishell.h"

#include <stdio.h>

int ft_check_lexer(char *line)
{
    if (!line)
    {
        printf("Erro: Linha é NULL\n");
        return (0);
    }

    if (!*line)
    {
        printf("Erro: Linha está vazia\n");
        return (0);
    }

    printf("Verificando se os operadores estão fechados...\n");
    if (!ft_check_closed_op(line))
    {
        printf("Erro: Operadores não fechados corretamente\n");
        return (0);
    }

    printf("Verificando a sintaxe do pipe...\n");
    if (!ft_check_pipe_syntax(line))
    {
        printf("Erro: Sintaxe de pipe incorreta\n");
        return (0);
    }

    printf("Verificando a sintaxe de redireção '<'...\n");
    if (!ft_check_redir_syntax(line, '<'))
    {
        printf("Erro: Sintaxe de redireção '<' incorreta\n");
        return (0);
    }

    printf("Verificando a sintaxe de redireção '>'...\n");
    if (!ft_check_redir_syntax(line, '>'))
    {
        printf("Erro: Sintaxe de redireção '>' incorreta\n");
        return (0);
    }

    printf("Lexical check passou com sucesso\n");
    return (1);
}
