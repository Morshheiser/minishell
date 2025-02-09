#include "../../include/minishell.h"

#include <stdio.h>

int main(int ac, char **av, char **ev)
{
    t_shell shell;
    
    // Inicializando shell
    printf("Iniciando a shell...\n");
    shell = start_function(av, ev);
    printf("Shell inicializada: %p\n", (void*)&shell);  // Imprime o endereço da shell
    
    (void) ac;  // Argumentos não utilizados, mas explicitamente indicados
    printf("Chamando ft_setsignal...\n");
    ft_setsignal();  // Configura os sinais (para captura de sinais como Ctrl-C, etc.)
    printf("Sinais configurados.\n");
    
    printf("Iniciando loop do minibash...\n");
    run_minibash_loop(&shell);  // Inicia o loop de execução do shell
    printf("Loop do minibash finalizado.\n");
    
    printf("Limpando recursos...\n");
    ft_cleanup_resources(&shell, shell.pd, shell.fd, shell.env);  // Limpeza de recursos
    printf("Recursos limpos.\n");
    
    return (42);  // Retorno padrão do programa
}
