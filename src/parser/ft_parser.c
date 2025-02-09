#include "../../include/minishell.h"

void parse_input(char *line, t_shell *shell)
{
    char **args;
    t_cmd *no;
    int i;
   
    // Verificação de linha vazia, se o conteúdo da linha for inválido
    if (!*line)  // Corrigindo a condição de verificação para linha vazia
    {
        printf("Linha vazia recebida: %s\n", line);
        return;
    }

    // Dividindo a linha com o delimitador "|"
    printf("Dividindo a linha usando o pipe '|': %s\n", line);
    args = ft_split_pipe(line, "|");
    if (!args)
    {
        printf("Erro ao dividir a linha com '|'.\n");
        return;
    }

    i = 0;
    while (args[i])
    {
        // Verificando o conteúdo de cada comando
        printf("Comando %d: %s\n", i, args[i]);

        // Inicializa e processa o comando atual
        printf("Processando comando: %s\n", args[i]);
        no = ft_init_and_process_command(args[i], shell);

        // Verificando se houve erro ao inicializar o comando
        if (!no)
        {
            printf("Erro ao processar o comando: %s\n", args[i]);
            ft_clean_cmd(&shell->cmd);
            break;
        }

        // Verificando o comando que foi retornado
        if (no)
        {
            printf("Comando processado com sucesso: %s\n", no->args[0]);
        }
        else
        {
            printf("Comando retornado é NULL\n");
        }

        // Adicionando o comando à lista de comandos
        printf("Adicionando comando à lista: %s\n", args[i]);
        ft_cmd_append(&shell->cmd, no);

        i++;
    }

    // Limpando a memória do array de comandos
    args = ft_clean_split(args);
    printf("Memória limpa para os comandos splitados.\n");

    // Verificando o conteúdo final de shell->cmd
    if (!shell->cmd)
    {
        printf("Erro: shell->cmd não foi populado corretamente.\n");
    }
    else
    {
        printf("Lista de comandos finalizada. Comando principal: %s\n", shell->cmd->args[0]);
    }
}
