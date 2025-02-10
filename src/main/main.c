#include "../../include/minishell.h"

#include <stdio.h>

int main(int ac, char **av, char **ev)
{
    t_shell shell;
    
    // Inicializando shell
    printf("Iniciando a shell...\n");
    shell = start_function(av, ev);
    (void) ac; 
    ft_setsignal();
    run_minibash_loop(&shell);  
    ft_cleanup_resources(&shell, shell.pd, shell.fd, shell.env); 
    return (42); 
}
