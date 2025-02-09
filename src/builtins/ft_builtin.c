#include "../../include/minishell.h"

#include "../../include/minishell.h"

void ft_execute_builtins(char **args, t_env *env, t_shell *shell)
{
    printf("[DEBUG] Executando builtin: %s\n", args[0]);

    if (ft_strncmp(args[0], "echo", 5) == 0) {
        printf("[DEBUG] Chamando builtin 'echo'.\n");
        ft_echo(args);
    }
    else if (ft_strncmp(args[0], "cd", 3) == 0) {
        printf("[DEBUG] Chamando builtin 'cd'.\n");
        ft_cd(args, env);
    }
    else if (ft_strncmp(args[0], "pwd", 4) == 0) {
        printf("[DEBUG] Chamando builtin 'pwd'.\n");
        ft_pwd(args, env);
    }
    else if (ft_strncmp(args[0], "export", 7) == 0) {
        printf("[DEBUG] Chamando builtin 'export'.\n");
        ft_export(args, env);
    }
    else if (ft_strncmp(args[0], "unset", 6) == 0) {
        printf("[DEBUG] Chamando builtin 'unset'.\n");
        ft_unset(args, env);
    }
    else if (ft_strncmp(args[0], "env", 4) == 0) {
        printf("[DEBUG] Chamando builtin 'env'.\n");
        ft_env(env);
    }
    else if (ft_strncmp(args[0], "exit", 5) == 0) {
        printf("[DEBUG] Chamando builtin 'exit'.\n");
        ft_exit(args, env, shell);
    } else {
        printf("[DEBUG] Nenhuma builtin correspondente encontrada para: %s\n", args[0]);
    }
}

void ft_builtin_exec(t_shell *shell, t_cmd *cmd)
{
    printf("[DEBUG] Executando comando builtin: %s\n", cmd->args[0]);

    if (!confirm(cmd)) {
        printf("[DEBUG] Comando não confirmado, abortando execução.\n");
        return;
    }

    printf("[DEBUG] Configurando descritores de arquivo...\n");
    ft_setfd(STDIN_FILENO, &cmd->fdin, STDIN_FILENO);
    ft_setfd(STDOUT_FILENO, &cmd->fdout, STDOUT_FILENO);

    printf("[DEBUG] Executando builtins...\n");
    ft_execute_builtins(cmd->args, shell->env, shell);

    printf("[DEBUG] Restaurando descritores de arquivo originais.\n");
    dup2(shell->fd[0], STDIN_FILENO);
    dup2(shell->fd[1], STDOUT_FILENO);
}

int ft_is_builtin(char *cmd)
{
    printf("[DEBUG] Verificando se '%s' é uma builtin...\n", cmd);

    // Declarando o array de ponteiros para strings
    const char *builtins[8];

    // Definindo as strings no array de builtins
    builtins[0] = "echo";
    builtins[1] = "cd";
    builtins[2] = "pwd";
    builtins[3] = "export";
    builtins[4] = "unset";
    builtins[5] = "env";
    builtins[6] = "exit";
    builtins[7] = NULL;  // Marcando o final do array

    int i = 0;
    // Percorrendo o array de builtins
    while (builtins[i]) {
        printf("[DEBUG] Comparando '%s' com '%s'...\n", builtins[i], cmd);

        // Comparando a string do comando com a builtin atual
        if (ft_strncmp(builtins[i], cmd, ft_strlen(builtins[i])) == 0) {
            printf("[DEBUG] '%s' é uma builtin!\n", cmd);
            return 1; // Retorna 1 se for uma builtin
        }
        i++;
    }

    // Se não encontrar, retorna 0
    printf("[DEBUG] '%s' não é uma builtin.\n", cmd);
    return 0;
}
