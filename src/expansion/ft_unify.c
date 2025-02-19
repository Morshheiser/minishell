#include "../../include/minishell.h"

char *ft_merge_strings(char *str1, char *str2)
{
    char *merge_str;

    if (str2 == NULL)
    {
        free(str1);
        return NULL;
    }
    merge_str = ft_check_alloc(ft_strjoin(str1, str2), "expansion");
    if (!merge_str)
    {
        free(str1);
        free(str2);
        return NULL;
    }
    free(str1);
    free(str2);
    return merge_str;
}
