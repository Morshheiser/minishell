#include "../../include/minishell.h"

#include <stdio.h>

int ft_check_lexer(char *line)
{
    if (!line || !*line)
        return (0);

    if (!ft_check_closed_op(line))
        return (0);
    if (!ft_check_pipe_syntax(line))
        return (0);
    if (!ft_check_redir_syntax(line, '<'))
        return (0);
    if (!ft_check_redir_syntax(line, '>'))
        return (0);
    return (1);
}
