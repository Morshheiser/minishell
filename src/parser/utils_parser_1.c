#include "../../include/minishell.h"

static char *ft_set_filename(char *input, t_shell *shell)
{
    char    *temp;
    char    *filename;
    char    quote_type;
    int     i;

    i = 0;
    while (ft_isspace(input[i]))
        i++;
    if ((input[i] == '\'') || (input[i] == '\"'))
    {
        quote_type = input[i++];
        while (input[i] != quote_type)
            i++;
        i++;
    }
    else
        while (input[i] && !ft_strchr("<>| \t\n\v\r\f", input[i]))
            i++;
    temp = ft_substr(input, 0, i);
    filename = ft_expand_variables(temp, shell->argv, shell->env->var_list);
    free(temp);
    return (ft_check_alloc(filename, "set_filename"));
}

static int ft_input_redirection(char *filename, t_fd *fd, int operator, t_shell *shell)
{
    t_fd temp_fd;

    if ((fd[IN].ffd == -1) || (fd[OUT].ffd == -1))
    {
        if (operator == 2)
        {
            temp_fd.fnm = ft_set_filename(filename, shell);
            if (!temp_fd.fnm)
                return (-1);
            temp_fd.ffd = ft_heredoc(temp_fd.fnm);
            ft_clean_fd(&temp_fd);
        }
        return (0);
    }
    ft_clean_fd(&fd[IN]);
    fd[IN].fnm = ft_set_filename(filename, shell);
    if (!fd[IN].fnm)
        return (-1);
    if (operator == 1)
        fd[IN].ffd = open(fd[IN].fnm, O_RDONLY, 00644);
    else if (operator == 2)
        fd[IN].ffd = ft_heredoc(fd[IN].fnm);
    return (0);
}

static int ft_output_redirection(char *filename, t_fd *fd, int operator, t_shell *shell)
{
    if ((fd[IN].ffd != -1) && (fd[OUT].ffd != -1))
    {
        ft_clean_fd(&fd[OUT]);
        fd[OUT].fnm = ft_set_filename(filename, shell);
        if (!fd[OUT].fnm)
            return (-1);
        if (operator == 1)
            fd[OUT].ffd = open(fd[OUT].fnm, O_WRONLY | O_CREAT | O_TRUNC, 00644);
        else if (operator == 2)
            fd[OUT].ffd = open(fd[OUT].fnm, O_WRONLY | O_CREAT | O_APPEND, 00644);
    }
    return (0);
}

int ft_configure_redirections(char *input, t_fd *fd, t_shell *shell)
{
    int count;
    char symbol;
    int i;
    
    i = 0;
    while (input[i])
    {
        count = 0;
        i += ft_find_quote_end(input);
        if (input[i] == '<' || input[i] == '>')
        {
            symbol = input[i];
            while (input[i + count] && input[i + count] == symbol)
                count++;
            i += count;
            if (symbol == '<')
            {
                if (ft_input_redirection(&input[i], fd, count, shell) < 0)
                    return (-1);
            }
            else if (symbol == '>')
            {
                if (ft_output_redirection(&input[i], fd, count, shell) < 0)
                    return (-1);
            }
        }
        else if (input[i])
            i++;
    }
    return (0);
}

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

t_cmd *ft_init_and_process_command(char *input, t_shell *shell)
{
    t_cmd  *cmd;
    t_fd    in_out[2];
    char    **args;

    in_out[IN].fnm = 0;
    in_out[IN].ffd = -2;
    in_out[OUT].fnm = 0;
    in_out[OUT].ffd = -2;
    args = 0;

    if (ft_configure_redirections(input, in_out, shell) < 0)
        return (ft_command_error(&in_out[IN], &in_out[OUT], args));
    ft_clean_redirection_tokens(input);
    args = ft_extract_command_arguments(input, shell);
    if (!args)
        return (ft_command_error(&in_out[IN], &in_out[OUT], args));
    cmd = ft_create_new_command(&in_out[IN], &in_out[OUT], args);
    if (!cmd)
        cmd = ft_command_error(&in_out[IN], &in_out[OUT], args);
    return (cmd);
}
