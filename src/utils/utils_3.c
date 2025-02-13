#include "../../include/minishell.h"

void ft_clean_int_fd(int *fd)
{
    if (*fd != -1) 
    {
        close(*fd); 
        *fd = -1;  
    }
}


