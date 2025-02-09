#include "../../include/minishell.h"

char *ft_set_prompt(char **env)
{
    char *prompt_string;
    char *username;
    char *cwd;
    char *prompt;

    username = ft_find_env_value("USER", env);
    if (!username)
        username = "usuário";
    cwd = getcwd(NULL, 0);
    if (!cwd)
        cwd = ft_strdup("~/");
    prompt_string = ft_strjoin(username, "@minishell:");
    prompt = ft_strjoin(prompt_string, cwd);
    free(prompt_string);
    prompt_string = ft_strjoin(prompt, "$ ");
    free(prompt);
    free(cwd);
    return (prompt_string);
}

void go_minibash(char *line, t_shell *shell)
{
    ft_executor(shell);
    if (shell->cmd)
        ft_clean_cmd(&shell->cmd);
    free(line);
}

void run_minibash_loop(t_shell *shell)
{
    char *prompt_template;
    char *input;

    while (1)
    {
        printf("Configurando prompt...\n");
        prompt_template = ft_set_prompt(shell->env->var_list);
        if (!prompt_template)
            return;
        input = readline(prompt_template);
        free(prompt_template);
        if (!input)
            ft_exit(0, shell->env, shell);
        printf("Entrada recebida: %s\n", input);
        if (!ft_str_is_space(input))
            add_history(input);
        if (ft_check_lexer(input))
            parse_input(input, shell);
    }
        go_minibash(input, shell);
}

