#include "minishell.h"

int do_tokens(char *rd_input)
{
    int     i;
    int     count;
    char    **splited;

    i = -1;
    count = -1;
    if (input_check(rd_input) != 0)
        return (input_check(rd_input));
    splited = mod_split_input(rd_input);
    if (!splited)
        return (ERROR_WORD);
    printf("Sucesso!\n");
    while (splited[++i] != NULL)
        printf("%d - |%s|\n", ++count, splited[i]);
    split_free(splited, i);
    return (0);
}