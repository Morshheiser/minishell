#include "../../include/minishell.h"

static char *ft_resolve_filename(char *input, t_shell *shell)
{
    char    *temp;
    char    *filename;
    int     index;
    char    quote_type;

    index = 0;
    while (ft_isspace(*input))
        input++;
    if ((input[index] == '\'') || (input[index] == '\"'))
    {
        quote_type = input[index++];
        while (input[index] != quote_type)
            index++;
        index++;
    }
    else
        while (input[index] && !ft_strchr("<>| \t\n\v\r\f", input[index]))
            index++;
    
    temp = ft_substr(input, 0, index);
    printf("Resolving filename from input: '%s' -> temp: '%s'\n", input, temp);
    filename = ft_expand_variables(temp, shell->argv, shell->env->var_list);
    free(temp);
    printf("Expanded filename: '%s'\n", filename);
    return (ft_check_alloc(filename, "resolve_filename"));
}

static int ft_input_redirection(char *filename, t_fd *fd_info, int operator, t_shell *shell)
{
    t_fd temp_fd;

    printf("Processing input redirection for filename: '%s' with operator: %d\n", filename, operator);

    if ((fd_info[IN].ffd == -1) || (fd_info[OUT].ffd == -1))
    {
        if (operator == 2)
        {
            temp_fd.fnm = ft_resolve_filename(filename, shell);
            if (!temp_fd.fnm)
                return (-1);
            temp_fd.ffd = ft_heredoc(temp_fd.fnm);
            ft_clean_fd(&temp_fd);
        }
        return (0);
    }
    ft_clean_fd(&fd_info[IN]);
    fd_info[IN].fnm = ft_resolve_filename(filename, shell);
    if (!fd_info[IN].fnm)
        return (-1);
    if (operator == 1)
        fd_info[IN].ffd = open(fd_info[IN].fnm, O_RDONLY, 00644);
    else if (operator == 2)
        fd_info[IN].ffd = ft_heredoc(fd_info[IN].fnm);
    printf("Input redirection set. File: '%s' with fd: %d\n", fd_info[IN].fnm, fd_info[IN].ffd);
    return (0);
}

static int ft_output_redirection(char *filename, t_fd *fd_info, int operator, t_shell *shell)
{
    printf("Processing output redirection for filename: '%s' with operator: %d\n", filename, operator);

    if ((fd_info[IN].ffd == -1) || (fd_info[OUT].ffd == -1))
        return (0);
    ft_clean_fd(&fd_info[OUT]);
    fd_info[OUT].fnm = ft_resolve_filename(filename, shell);
    if (!fd_info[OUT].fnm)
        return (-1);
    if (operator == 1)
        fd_info[OUT].ffd = open(fd_info[OUT].fnm, O_WRONLY | O_CREAT | O_TRUNC, 00644);
    else if (operator == 2)
        fd_info[OUT].ffd = open(fd_info[OUT].fnm, O_WRONLY | O_CREAT | O_APPEND, 00644);
    printf("Output redirection set. File: '%s' with fd: %d\n", fd_info[OUT].fnm, fd_info[OUT].ffd);
    return (0);
}

int ft_configure_redirections(char *input, t_fd *fd_info, t_shell *shell)
{
    int count;
    char symbol;
    int index = 0;

    printf("Configuring redirections for input: '%s'\n", input);
    while (input[index])
    {
        count = 0;
        index += ft_find_quote_end(&input[index]);
        if (input[index] == '<' || input[index] == '>')
        {
            symbol = input[index];
            while (input[index + count] && input[index + count] == symbol)
                count++;
            index += count;
            if (symbol == '<')
            {
                printf("Found input redirection symbol: '%c'\n", symbol);
                if (ft_input_redirection(&input[index], fd_info, count, shell) < 0)
                    return (-1);
            }
            else if (symbol == '>')
            {
                printf("Found output redirection symbol: '%c'\n", symbol);
                if (ft_output_redirection(&input[index], fd_info, count, shell) < 0)
                    return (-1);
            }
        }
        else if (input[index])
            index++;
    }
    return (0);
}

t_cmd *ft_init_and_process_command(char *input, t_shell *shell)
{
    t_cmd  *cmd;
    t_fd    in_out[2];
    char    **args;

    // Inicializando os descritores de arquivos para entrada e saída
    in_out[IN].fnm = 0;
    in_out[IN].ffd = -2;
    in_out[OUT].fnm = 0;
    in_out[OUT].ffd = -2;
    args = 0;

    // Configuração de redirecionamento
    if (ft_configure_redirections(input, in_out, shell) < 0)
    {
        return (ft_command_error(&in_out[IN], &in_out[OUT], args));
    }

    // Limpeza de redirecionamento
    ft_clean_redirection_tokens(input);

    // Extração dos argumentos do comando
    args = ft_extract_command_arguments(input, shell);
    if (!args)
    {
        return (ft_command_error(&in_out[IN], &in_out[OUT], args));
    }

    // Criação do comando com os argumentos extraídos
    cmd = ft_create_new_command(&in_out[IN], &in_out[OUT], args);
    if (!cmd)
    {
        cmd = ft_command_error(&in_out[IN], &in_out[OUT], args);
    }

    return (cmd);
}

t_cmd *ft_create_command_from_input(char *input, t_shell *shell)
{
    t_cmd  *cmd;
    t_fd    input_output[2];
    char    **args;

    // Inicializando os descritores de arquivos para entrada e saída
    input_output[IN].fnm = 0;
    input_output[IN].ffd = -2;
    input_output[OUT].fnm = 0;
    input_output[OUT].ffd = -2;
    args = 0;

    // Processamento do comando com configuração de redirecionamento
    cmd = ft_init_and_process_command(input, shell);
    if (!cmd)
    {
        printf("Error creating command. Returning error command.\n");
        cmd = ft_command_error(&input_output[IN], &input_output[OUT], args);
    }

    return (cmd);
}
