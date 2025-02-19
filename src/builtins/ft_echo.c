#include "../../include/minishell.h"
// rever essa função
// observação rever novamente
int ft_echo(char **args)
{
    int i;
    int new_line;
    int j;

    i = 1;
    new_line = 1;

    while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        j = 1;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] != '\0')
            break;
        new_line = 0;
        i++;
    }

    if (!(args[i] && args[i][0] == '-' && args[i][1] == 'n'))
    {
        new_line = 1;
    }

    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[++i])
            ft_putstr_fd(" ", STDOUT_FILENO);
    }

    if (new_line)
        ft_putchar_fd('\n', STDOUT_FILENO);

    status_g = 0;
    return 0;
}
