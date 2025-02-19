#include "../../include/minishell.h"

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

void ft_specific(int fd[2], int *prev_pipe_read, t_cmd *cmd, t_shell *shell)
{
    close(fd[0]);
    ft_setfd(fd[1], &cmd->fdout, STDOUT_FILENO);
    close(fd[1]);
    ft_setfd(*prev_pipe_read, &cmd->fdin, STDIN_FILENO);
    close(*prev_pipe_read);
    ft_reset_signal();
    if (ft_is_builtin(cmd->args[0]))
    {
        ft_builtin_exec(shell, cmd);
        ft_clean_sh(shell);
	    exit(0);
    }
    else
        ft_execve_exec(shell, cmd);
}