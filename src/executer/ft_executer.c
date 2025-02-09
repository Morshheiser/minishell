#include "../../include/minishell.h"

void ft_executor(t_shell *shell)
{
    t_cmd   *cmd;
    int builtin;
    int original_pipe;

    if (!shell || !shell->cmd)
    {
        printf("Erro: shell ou cmd são NULL\n");
        return;
    }

    cmd = shell->cmd;
    printf("Iniciando execução com cmd->args: %s\n", cmd->args ? cmd->args[0] : "NULL");

    // Se o comando é o único e é um comando built-in, executa-o
    if ((!cmd->next) && ft_is_builtin(*shell->cmd->args))
    {
        printf("Comando único e built-in encontrado. Executando built-in.\n");
        ft_builtin_exec(shell, cmd);
        return;
    }

    original_pipe = dup(0);  // Salva o descritor original de stdin
    if (original_pipe == -1)
    {
        perror("Erro ao duplicar o pipe original");
        return;
    }
    printf("Pipe original duplicado: %d\n", original_pipe);

    // Processa a lista de comandos
    while (cmd)
    {
        printf("Processando comando: %s\n", cmd->args ? cmd->args[0] : "NULL");

        if (ft_is_builtin(*shell->cmd->args))
        {
            printf("Comando é um built-in. Executando built-in.\n");
            ft_builtin_exec(shell, cmd);
        }
        else
        {
            printf("Comando não é built-in. Processando o pipeline.\n");
            process_command_pipeline(original_pipe, shell, shell->cmd);
        }

        cmd = cmd->next;
        if (cmd)
            printf("Passando para o próximo comando na lista.\n");
        else
            printf("Fim da lista de comandos.\n");
    }
}
