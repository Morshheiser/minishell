#include "../../include/minishell.h"

void ft_executor(t_shell *shell)
{
    t_cmd   *cmd;
    int builtin;
    int original_pipe;

    if (!shell || !shell->cmd)
        return;
    cmd = shell->cmd;
    if ((!cmd->next) && ft_is_builtin(*shell->cmd->args))
    {
        ft_builtin_exec(shell, cmd);
        return;
    }
    original_pipe = dup(0); 
    process_command_pipeline(original_pipe, shell, cmd);
}

void process_command_pipeline(int orig_pipe, t_shell *shell, t_cmd *cmd)
{
    t_pid *list = NULL;

    while (cmd)
    {
        if (!cmd->next)
            end_exec(orig_pipe, cmd, shell, &list);
        else
            begin_exec(&orig_pipe, cmd, shell, &list);
        cmd = cmd->next;
    }
}


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

    if (!confirm(cmd))
        return;
    pid = fork();
    if (!pid)
    {
        ft_reset_signal();
        ft_setfd(shell->fd[1], &cmd->fdout, STDOUT_FILENO);
        ft_setfd(pipe_out, &cmd->fdin, STDIN_FILENO);
        close(pipe_out);
        if (ft_is_builtin(*cmd->args))
        {
            ft_builtin_exec(shell, cmd);
            ft_clean_sh(shell);
            exit(0);
        }
        else
            ft_execve_exec(shell, cmd);
    }
    else
    {
        close(pipe_out);
        ft_add_back_pid(lst_pid, ft_new_pid(pid));
        if(pid > 0)
            ft_wait_pid(lst_pid);
    }
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
    execve(pathname, cmd->args, shell->env->var_list);

}
