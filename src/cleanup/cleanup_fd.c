#include "../../include/minishell.h"

void ft_cleanup_fd(int *fd)
{
        if (fd[0] != -1)
            close(fd[0]);
        if (fd[1] != -1)
            close(fd[1]);
}
void ft_clean_int_fd(int *fd)
{
    if (*fd != -1) 
    {
        close(*fd); 
        *fd = -1;  
    }
}

