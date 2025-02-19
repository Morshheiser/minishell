#include "../../include/minishell.h"

void go_minibash(char *line, t_shell *shell)
{
    ft_executor(shell);
    ft_clean_cmd(&shell->cmd);
    free(line);
}
void run_minibash_loop(t_shell *shell)
{
    char *prompt_template;
    char *input;

    while (1)
    {
        prompt_template = ft_set_prompt(shell->env->var_list);
        if (!prompt_template)
            return;
        input = readline(prompt_template);
        free(prompt_template);
        if (!input)
            ft_exit(0, shell->env, shell);
        if (ft_check_lexer(input))
            parse_input(input, shell);
        if (!ft_str_is_space(input))
            add_history(input);
        go_minibash(input, shell);
    }
}

int main(int ac, char **av, char **ev)
{
    t_shell shell;
   
    printf("\nIniciando a shell...\n\n");
    shell = start_function(av, ev);
    ft_setup_signal_handlers();
    (void) ac;
    run_minibash_loop(&shell);
    ft_cleanup_resources(&shell, shell.pd, shell.fd, shell.env);
    rl_clear_history();
    return (42); 
}
