#include "../../include/minishell.h"

int main(int ac, char **av, char **ev)
{
    t_shell shell;
   
    printf("\nIniciando a shell...\n\n");
    shell = start_function(av, ev);
    ft_setup_signal_handlers();
    (void) ac;
    run_minibash_loop(&shell);
    rl_clear_history();
    ft_cleanup_resources(&shell, shell.pd, shell.fd, shell.env);
    rl_clear_history();
    return (42); 
}
