#include "../../include/minishell.h"

void ft_clean_sh(t_shell *shell)
{
	close(shell->fd[IN]);
	close(shell->fd[OUT]);
	ft_clean_cmd(&shell->cmd);    
}