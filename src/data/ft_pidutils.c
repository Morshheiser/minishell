#include "../../include/minishell.h"

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