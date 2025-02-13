#include "../../include/minishell.h"
void begin_exec(int *pipe_in, t_cmd *cmd, t_shell *shell, t_pid **lst_pid)
{
    int pid;
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return;
    }
    if (!confirm(cmd))
    {
        close(*pipe_in);
        close(fd[1]);
        *pipe_in = fd[0];
        return;
    }
    pid = fork();
    if (pid == 0)
        ft_specific(fd, pipe_in, cmd, shell);
    else
    {
        ft_add_back_pid(lst_pid, ft_new_pid(pid));
        close(fd[1]);
        close(*pipe_in);
        *pipe_in = fd[0];
    }
}

void end_exec(int pipe_out, t_cmd *cmd, t_shell *shell, t_pid **lst_pid)
{
    int pid;



    if (!cmd->args || !cmd->args[0] || !confirm(cmd))
        return;
    pid = fork();
    if (!pid)
    {
        ft_reset_signal();
        ft_setfd(shell->fd[1], &cmd->fdout, STDOUT_FILENO);
        ft_setfd(pipe_out, &cmd->fdin, STDIN_FILENO);
        close(pipe_out);
        if (ft_is_builtin(*cmd->args))
            ft_builtin_exec(shell, cmd);
        else
            ft_execve_exec(shell, cmd);
    }
    else
    {
        close(pipe_out);
        ft_add_back_pid(lst_pid, ft_new_pid(pid));
        ft_wait_pid(lst_pid);
    }
}

void process_command_pipeline(int orig_pipe, t_shell *shell, t_cmd *cmd)
{
    t_pid *list;

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
    if (!cmd || !cmd->args || !cmd->args[0])
        return (0);
    if (cmd->fdout.ffd == -1 && access(cmd->args[0], F_OK | W_OK) != 0)
    {
        status_g = ft_perror(1, cmd->args[0], 0);
        return (0);
    }
    if (cmd->fdin.ffd == -1 && access(cmd->args[0], F_OK | R_OK) != 0)
    {
        status_g = ft_perror(1, cmd->args[0], 0);
        return (0);
    }
    return (1);
}

void ft_setfd(int fd, t_fd *files, int s)
{
    if (files->ffd != -2)
    {
        dup2(files->ffd, s);
        ft_clean_fd(files);
    }
    else if (fd != s)
        (dup2(fd, s) == -1);
}


void ft_specific(int fd[2], int *prev_pipe_read, t_cmd *cmd, t_shell *shell)
{
    close(fd[0]);
    if (cmd->fdout.ffd != -1)
        ft_setfd(fd[1], &cmd->fdout, STDOUT_FILENO);
    close(fd[1]);
    if (*prev_pipe_read != -1)
        ft_setfd(*prev_pipe_read, &cmd->fdin, STDIN_FILENO);
    close(*prev_pipe_read);
    ft_reset_signal();
    if (ft_is_builtin(cmd->args[0]))
        ft_builtin_exec(shell, cmd);
    else
        ft_execve_exec(shell, cmd);
}

void ft_wait_pid(t_pid **pid)
{
    t_pid *c_pid;
    int status;

    status = 0;
    c_pid = *pid;
    while (c_pid)
    {
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
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

char *ft_get_path_name(char *cmd, t_env *env_list)
{
    char *full_path;
    char *env_path;

    if (!cmd || !env_list)
        return NULL;

    if (ft_strchr(cmd, '/'))
        return ft_handle_absolute_path(cmd);
    env_path = ft_find_env_value("PATH", env_list->var_list);
    if (!env_path)
    {
        status_g = ft_perror(127, cmd, "ft_get_path_name: Caminho não encontrado no PATH\n");
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
            return aux;
        }
        free(aux);
    }
    ft_clean_split(path);
    status_g = ft_perror(127, cmd, "command not found");
    return NULL;
}

void ft_execve_exec(t_shell *shell, t_cmd *cmd)
{
    char *pathname;

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
    execve(pathname, cmd->args, shell->env->var_list);
    free(pathname);
    ft_clean_sh(shell);
}

char *ft_handle_absolute_path(char *cmd)
{
    if (access(cmd, F_OK | X_OK) != 0)
    {
        status_g = ft_perror(126 + (errno == ENOENT), cmd, NULL);
        return NULL;
    }
    return ft_strdup(cmd);
}
