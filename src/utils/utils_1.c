#include "../../include/minishell.h"

void	*ft_check_alloc(void *str, char *text)
{
	if (str == NULL)
	{
		errno = ENOMEM;
		ft_perror(0, text, 0);
	}
	return (str);
}

t_cmd	*ft_new_cmd(t_fd *in, t_fd *out, char **args)
{
	t_cmd	*arg;

	arg = ft_calloc(sizeof(t_cmd), 1);
	if (arg)
	{
		arg->fdin.ffd = in->ffd;
		arg->fdin.fnm = in->fnm;
		arg->fdout.ffd = out->ffd;
		arg->fdout.fnm = out->fnm;
		arg->args = args;
		arg->next = 0;
	}
	return (ft_check_alloc(arg, "cmd_new"));
}

void ft_clean_cmd(t_cmd **cmd)
{
    t_cmd *current_cmd;

    if (!cmd || !*cmd)
        return;
    while (*cmd)
    {
        current_cmd = *cmd;
        *cmd = current_cmd->next;
	    ft_clean_fd(&current_cmd->fdin);
        ft_clean_fd(&current_cmd->fdout);
        if (current_cmd->args)
            current_cmd->args = ft_clean_split(current_cmd->args);
        free(current_cmd);
    }
}
//msh_cmdadd_back
void ft_cmd_append(t_cmd **cmd_list, t_cmd *new_cmd)
{
    if (!cmd_list || !new_cmd)
        return;

    new_cmd->next = NULL;

    if (!*cmd_list)
    {
        *cmd_list = new_cmd;
        return;
    }
    t_cmd *last = *cmd_list;
    while (last->next)
        last = last->next;
    last->next = new_cmd;
}

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
        fd->fnm = NULL;
    }
}


t_pid *ft_new_pid(int pid)
{
    t_pid *node;

    node = ft_calloc(sizeof(t_pid),1);
    if (!node)
        return NULL; 
    node->pid = pid;
    node->next = (void *)0;
    return ft_check_alloc(node, "New_pid");
}

void ft_add_back_pid(t_pid **pid, t_pid *node)
{
    t_pid *current;

    if (!*pid)
	{
        *pid = node;
        return;
    }
    current = *pid;
    while (current->next)
	    current = current->next;
    current->next = node;
}


void	ft_clean_pid(t_pid **pid)
{
	t_pid	*next;

	if (!pid)
		return ;
	while (*pid)
	{
		next = (**pid).next;
		free (*pid);
		*pid = next;
	}
}

void ft_clean_sh(t_shell *shell)
{
	close(shell->fd[IN]);
	close(shell->fd[OUT]);
	ft_clean_cmd(&shell->cmd);    
}

char	**ft_clean_split(char **split)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
	{
		free (split[i]);
		i++;
	}
	free (split);
	return (0);
}
