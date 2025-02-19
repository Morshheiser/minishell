#include "../../include/minishell.h"
//nao achei
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
//nao encontrei
t_cmd *ft_create_command_from_input(char *input, t_shell *shell)
{
    t_cmd  *cmd;
    t_fd    in_out[2];
    char    **args;

    in_out[IN].fnm = 0;
    in_out[IN].ffd = -2;
    in_out[OUT].fnm = 0;
    in_out[OUT].ffd = -2;
    args = 0;
    cmd = ft_init_and_process_command(input, shell);
    if (!cmd)
    {
        printf("Error creating command. Returning error command.\n");
        cmd = ft_command_error(&in_out[IN], &in_out[OUT], args);
    }
    return (cmd);
}

//nao achei
t_cmd	*ft_new_cmd(t_fd *in, t_fd *out, char **args)
{
	t_cmd	*arg;

	arg = ft_calloc(sizeof(t_cmd), 1);
	if (arg)
	{
		arg->fdin.ffd = in->ffd;
		arg->fdin.fnm = in->fnm;
		arg->fdout.ffd = out->ffd;
		arg->fdout.fnm = out->fnm;
		arg->args = args;
		arg->next = 0;
	}
	return (ft_check_alloc(arg, "cmd_new"));
}




void change_flag(char c, int *single_flag, int *double_flag)
{

    if (c == '\'' && *double_flag == 0)
        *single_flag = !(*single_flag);
    else if (c == '\"' && *single_flag == 0)
        *double_flag = !(*double_flag);

}


int ft_count_pipe(char *str)
{
    int i;
    int count;
    int single_flag;
    int double_flag;

    i = -1;
    count = 0;
    single_flag = 0;
    double_flag = 0;
    while (str[++i])
    {
        change_flag(str[i], &single_flag, &double_flag);
        if ((str[i] == 124) && !single_flag && !double_flag)
            count++;
    }
    return (count);
}

