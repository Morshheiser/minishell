#include "../../include/minishell.h"

char *ft_set_prompt(char **env)
{
    char *prompt_string;
    char *username;
    char *prompt;

    username = ft_find_env_value("USER", env);
    if (!username)
        prompt_string = ft_strjoin("usuario", "@minishell:");
    else
    {
        prompt_string = ft_strjoin(username, "@minishell:");
        free(username);
    }
    prompt = ft_strjoin(prompt_string, "$ ");
    free(prompt_string);
    return (prompt);
}

