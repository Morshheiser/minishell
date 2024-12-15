#include "minishell.h"

int input_check(char *str)
{
    if (!all_quotes_has_end(str))
		return (ERROR_QUOTE);
    //criar a função que verifica PIPE
    return (0);
}