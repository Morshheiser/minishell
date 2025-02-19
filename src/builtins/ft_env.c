#include "../../include/minishell.h"
//rever
int	ft_env(t_env *env)
{
	t_env *current;
	int i;

	if (!env || !env->var_list)
	{
		status_g = 1; 
		return (EXIT_FAILURE);
	}

	current = env;
	i = -1;
	while (current->var_list[++i])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putstr_fd(current->var_list[i], STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	status_g = 0;
	return (EXIT_SUCCESS);
}

