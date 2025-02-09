#include "../../include/minishell.h"

char *ft_set_prompt(char **env)
{
    char *prompt_string;
    char *username;
    char *cwd;
    char *prompt;

    username = ft_find_env_value("USER", env);
    printf("Nome de usuário: %s\n", username ? username : "usuário");

    if (!username)
        username = "usuário";

    cwd = getcwd(NULL, 0);
    printf("Diretório de Trabalho Atual: %s\n", cwd ? cwd : "NULL");

    if (!cwd)
        cwd = ft_strdup("~/");

    prompt_string = ft_strjoin(username, "@minishell:");
    prompt = ft_strjoin(prompt_string, cwd);
    free(prompt_string);

    printf("Prompt (antes de adicionar $): %s\n", prompt);

    prompt_string = ft_strjoin(prompt, "$ ");
    free(prompt);

    printf("Prompt final: %s\n", prompt_string);

    free(cwd);
    return (prompt_string);
}

void go_minibash(char *line, t_shell *shell)
{
    printf("Executando comando...\n");

    // Verificando o valor de shell->cmd antes de executar
    if (!shell->cmd)
    {
        printf("Erro: shell->cmd é NULL antes de executar!\n");
    }
    else
    {
        // Corrigido para iterar sobre os argumentos
        if (shell->cmd->args)
        {
            printf("Comando encontrado: ");
            for (int i = 0; shell->cmd->args[i] != NULL; i++) {
                printf("%s ", shell->cmd->args[i]);  // Imprime cada argumento
            }
            printf("\n");
        }
        else
        {
            printf("Comando encontrado, mas sem argumentos associados!\n");
        }
    }

    ft_executor(shell);

    // Verificação pós-execução
    if (shell->cmd)
    {
        printf("Limpeza de comandos...\n");
        ft_clean_cmd(&shell->cmd);
    }
    else
    {
        printf("Comando não encontrado! cmd é NULL\n");
    }

    free(line);
}

void run_minibash_loop(t_shell *shell)
{
    char *prompt_template;
    char *input;
    char *input_start;

    while (1)
    {
        printf("Configurando prompt...\n");
        prompt_template = ft_set_prompt(shell->env->var_list);
        if (!prompt_template)
        {
            printf("Falha ao gerar o prompt, saindo...\n");
            return;
        }

        printf("Prompt: %s\n", prompt_template);
        input = readline(prompt_template);
        free(prompt_template);

        if (!input)
        {
            printf("Nenhuma entrada recebida, saindo...\n");
            ft_exit(0, shell->env, shell);
        }

        printf("Entrada recebida: %s\n", input);

        if (ft_check_lexer(input))
        {
            printf("Entrada válida, analisando...\n");
            parse_input(input, shell);  // Verifique o que acontece dentro de parse_input
            if (!shell->cmd)
            {
                printf("Erro: shell->cmd não foi configurado após o parsing!\n");
            }
            else
            {   
            printf("Comando configurado com sucesso: %s\n", shell->cmd->args[0]);
            }
        }

        input_start = input;
        if (!ft_str_is_space(input_start))
        {
            printf("Entrada não vazia, adicionando ao histórico...\n");
            add_history(input);
        }

        go_minibash(input, shell);
    }
}
