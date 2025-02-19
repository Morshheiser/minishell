#include "../../include/minishell.h"

t_shell start_function(char **argv, char **env)
{
    t_shell shell;
    
    ft_memset(&shell, 0, sizeof(t_shell));
    shell.argv = argv;
    shell.fd[0] = dup(STDIN_FILENO);
    shell.fd[1] = dup(STDOUT_FILENO);
    ft_initialize_env(&shell.env, env);
    return (shell);
}


