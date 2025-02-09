#include "../../include/minishell.h"
void begin_exec(int *pipe_in, t_cmd *cmd, t_shell *shell, t_pid **lst_pid)
{
    int pid;
    int fd[2];

    printf("begin_exec: Iniciando execução\n");

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return;
    }

    if (!confirm(cmd))
    {
        printf("begin_exec: Confirmação falhou. Fechando pipe.\n");
        close(*pipe_in);
        close(fd[1]);
        *pipe_in = fd[0];
        return;
    }

    pid = fork();
    printf("begin_exec: PID do fork: %d\n", pid);

    if (pid == 0)
    {
        printf("begin_exec: Processo filho. Executando ft_specific.\n");
        ft_specific(fd, pipe_in, cmd, shell);
    }
    else
    {
        printf("begin_exec: Processo pai. Adicionando PID à lista.\n");
        ft_add_back_pid(lst_pid, ft_new_pid(pid));
        close(fd[1]);
        close(*pipe_in);
        *pipe_in = fd[0];
    }
}

void end_exec(int pipe_out, t_cmd *cmd, t_shell *shell, t_pid **lst_pid)
{
    int pid;

    printf("end_exec: Iniciando execução\n");

    if (!cmd->args || !cmd->args[0] || !confirm(cmd))
    {
        printf("end_exec: Comando inválido ou confirmação falhou\n");
        return;
    }

    pid = fork();
    printf("end_exec: PID do fork: %d\n", pid);

    if (!pid)
    {
        printf("end_exec: Processo filho. Executando o comando.\n");
        ft_reset_signal();
        ft_setfd(shell->fd[1], &cmd->fdout, STDOUT_FILENO);
        ft_setfd(pipe_out, &cmd->fdin, STDIN_FILENO);
        close(pipe_out);

        if (ft_is_builtin(*cmd->args))
        {
            printf("end_exec: Comando é builtin. Executando ft_builtin_exec.\n");
            ft_builtin_exec(shell, cmd);
        }
        else
        {
            printf("end_exec: Comando não é builtin. Executando ft_execve_exec.\n");
            ft_execve_exec(shell, cmd);
        }
    }
    else
    {
        printf("end_exec: Processo pai. Fechando pipe e aguardando PID.\n");
        close(pipe_out);
        ft_add_back_pid(lst_pid, ft_new_pid(pid));
        ft_wait_pid(lst_pid);
    }
}

void process_command_pipeline(int orig_pipe, t_shell *shell, t_cmd *cmd)
{
    t_pid *list;

    printf("process_command_pipeline: Processando pipeline\n");

    list = 0;
    while (shell->cmd)
    {
        if (!shell->cmd->next)
            end_exec(orig_pipe, cmd, shell, &list);
        else
            begin_exec(&orig_pipe, cmd, shell, &list);
        
        shell->cmd = shell->cmd->next;
    }
}

int confirm(t_cmd *cmd)
{
    printf("confirm: Verificando comando\n");

    if (!cmd || !cmd->args || !cmd->args[0])
    {
        printf("confirm: Comando inválido\n");
        return (0);
    }

    if (cmd->fdout.ffd == -1 && access(cmd->args[0], F_OK | W_OK) != 0)
    {
        status_g = ft_perror(1, cmd->args[0], 0);
        printf("confirm: Erro ao acessar o arquivo para escrita\n");
        return (0);
    }

    if (cmd->fdin.ffd == -1 && access(cmd->args[0], F_OK | R_OK) != 0)
    {
        status_g = ft_perror(1, cmd->args[0], 0);
        printf("confirm: Erro ao acessar o arquivo para leitura\n");
        return (0);
    }

    printf("confirm: Comando confirmado\n");
    return (1);
}

void ft_setfd(int fd, t_fd *files, int s)
{
    printf("ft_setfd: Configurando o file descriptor\n");

    if (files->ffd != -2)
    {
        printf("ft_setfd: Redirecionando para o file descriptor %d\n", files->ffd);
        if (dup2(files->ffd, s) == -1)
        {
            perror("Erro ao redirecionar o descritor de arquivo");
            return;
        }
        ft_clean_fd(files);
    }
    else if (fd != s)
    {
        printf("ft_setfd: Redirecionando para o pipe fd\n");
        if (dup2(fd, s) == -1)
        {
            perror("Erro ao redirecionar para o pipe");
            return;
        }
    }
}



void ft_specific(int fd[2], int *prev_pipe_read, t_cmd *cmd, t_shell *shell)
{
    printf("ft_specific: Executando comando específico\n");

    close(fd[0]);

    if (cmd->fdout.ffd != -1)
    {
        printf("ft_specific: Redirecionando saída para fd[1]\n");
        ft_setfd(fd[1], &cmd->fdout, STDOUT_FILENO);
    }

    close(fd[1]);

    if (*prev_pipe_read != -1)
    {
        printf("ft_specific: Redirecionando entrada de %d\n", *prev_pipe_read);
        ft_setfd(*prev_pipe_read, &cmd->fdin, STDIN_FILENO);
    }

    close(*prev_pipe_read);
    ft_reset_signal();

    if (ft_is_builtin(cmd->args[0]))
    {
        printf("ft_specific: Comando é builtin. Executando ft_builtin_exec.\n");
        ft_builtin_exec(shell, cmd);
    }
    else
    {
        printf("ft_specific: Comando não é builtin. Executando ft_execve_exec.\n");
        ft_execve_exec(shell, cmd);
    }
}

void ft_wait_pid(t_pid **pid)
{
    t_pid *c_pid;
    int status;

    printf("ft_wait_pid: Esperando processos filhos\n");

    status = 0;
    c_pid = *pid;
    while (c_pid)
    {
        printf("ft_wait_pid: Aguardando o PID %d\n", c_pid->pid);
        if (waitpid(c_pid->pid, &status, 0) == -1)
        {
            perror("Error waiting for process");
            c_pid = c_pid->next;
            continue;
        }
        if (WIFEXITED(status))
            status_g = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            status_g = 128 + WTERMSIG(status);
        c_pid = c_pid->next;
    }

    ft_clean_pid(pid);
}

void ft_reset_signal(void)
{
    printf("ft_reset_signal: Resetando sinais SIGINT e SIGQUIT\n");
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

char *ft_get_path_name(char *cmd, t_env *env_list)
{
    char *full_path;
    char *env_path;

    printf("ft_get_path_name: Obtendo caminho do comando\n");

    if (!cmd || !env_list)
        return NULL;

    if (ft_strchr(cmd, '/'))
    {
        printf("ft_get_path_name: Caminho absoluto encontrado\n");
        return ft_handle_absolute_path(cmd);
    }

    env_path = ft_find_env_value("PATH", env_list->var_list);
    if (!env_path)
    {
        status_g = ft_perror(127, cmd, "command not found");
        printf("ft_get_path_name: Caminho não encontrado no PATH\n");
        return NULL;
    }

    full_path = ft_find_relative(cmd, env_path);
    free(env_path);
    return full_path;
}

char *ft_find_relative(char *cmd, char *env)
{
    char **path;
    char *aux;
    int i;
    char *full_path;

    printf("ft_find_relative: Buscando comando relativo no PATH\n");

    path = ft_split(env, ':');
    if (!path)
        return NULL;

    i = -1;
    while (path[++i])
    {
        full_path = ft_strjoin(path[i], "/");
        if (!full_path)
            break;

        aux = ft_strjoin(full_path, cmd);
        free(full_path);

        if (aux && access(aux, F_OK | X_OK) == 0)
        {
            ft_clean_split(path);
            printf("ft_find_relative: Comando encontrado: %s\n", aux);
            return aux;
        }
        free(aux);
    }

    ft_clean_split(path);
    status_g = ft_perror(127, cmd, "command not found");
    printf("ft_find_relative: Comando não encontrado no PATH\n");
    return NULL;
}

void ft_execve_exec(t_shell *shell, t_cmd *cmd)
{
    char *pathname;

    printf("ft_execve_exec: Executando comando\n");

    pathname = ft_get_path_name(cmd->args[0], shell->env);
    if (!pathname)
    {
        ft_clean_sh(shell);
        exit(127);
    }

    if (cmd->fdin.ffd != -1)
        ft_setfd(cmd->fdin.ffd, &cmd->fdin, STDIN_FILENO); 
    if (cmd->fdout.ffd != -1)
        ft_setfd(cmd->fdout.ffd, &cmd->fdout, STDOUT_FILENO);

    printf("ft_execve_exec: Executando execve com o caminho: %s\n", pathname);
    execve(pathname, cmd->args, shell->env->var_list);
    free(pathname);
    ft_clean_sh(shell);
}

char *ft_handle_absolute_path(char *cmd)
{
    printf("ft_handle_absolute_path: Verificando caminho absoluto\n");

    if (access(cmd, F_OK | X_OK) != 0)
    {
        status_g = ft_perror(126 + (errno == ENOENT), cmd, NULL);
        printf("ft_handle_absolute_path: Erro ao acessar o comando\n");
        return NULL;
    }

    printf("ft_handle_absolute_path: Caminho absoluto válido\n");
    return ft_strdup(cmd);
}
