#include "../../include/minishell.h"

void ft_clean_fd(t_fd *fd)
{
    if (!fd)
        return;
    if (fd->ffd != -1 && fd->ffd != -2)
    {
        close(fd->ffd);
        fd->ffd = -2;
    }
    if (fd->fnm)
    {
        free(fd->fnm);
        fd->fnm = 0;
    }
}