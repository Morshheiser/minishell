#include "../../include/minishell.h"

//ok
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

t_cmd	*ft_command_error(t_fd *in, t_fd *out, char **split)
{
	printf("ft_command_error: Cleaning up split and file descriptors\n");
	split = ft_clean_split(split);
	ft_clean_fd(in);
	ft_clean_fd(out);
	return (0);
}
//ok

void	ft_handle_redirection(char *str)
{
	int i = 0;

	while (str[i] == '<' || str[i] == '>')
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\'' || str[i] == '"')
		i += ft_find_quote_end(str + i) + 1;
	else
		while (str[i] && !ft_strchr("<>| \t\n\v\r\f", str[i]))
			i++;
	ft_memset(str, ' ', i);
}

//ok
void	ft_clean_redirection_tokens(char *str)
{
	while (*str)
	{
		str += ft_find_quote_end(str);
		if (*str == '<' || *str == '>')
			ft_handle_redirection(str);
		else if (*str >= 9 && *str <= 13)
			*str = ' ';
		str++;
	}
}


int ft_process_argument(char **args, int index, t_shell *shell)
{
    char *expanded;
    int j;

    expanded = ft_expand_variables(args[index], shell->argv, shell->env->var_list);
    free(args[index]);

    if (!expanded)
    {
        j = index;
        while (args[j])
        {
            args[j] = args[j + 1];
            j++;
        }

        return (0);
    }

    args[index] = expanded;

    return (1);
}

char **ft_extract_command_arguments(char *line, t_shell *shell)
{
    char **args;
    int i;

    args = ft_split_with_set(line, " \t\n\v\f\r");

    if (!args)
    {
        return (NULL);
    }

    i = 0;
    while (args[i])
    {
        if (!ft_process_argument(args, i, shell))
            continue;

        i++;
    }

    return (args);
}
