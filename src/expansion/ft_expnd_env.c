#include "../../include/minishell.h"
// ok
char *ft_expand_env_variable(char **input, char **args, char **env)
{
    char *result;
    char next_char;

    result = NULL;
    next_char = *(*input + 1);
    if (next_char == '?')
    {
        result = ft_itoa(status_g);
        *input = *input + 2;
    }
    else if (next_char == '{')
        result = ft_get_env_in_brackets(input, env);
    else if (ft_isdigit(next_char))
        result = ft_get_arg_value(input, args);
    else if (ft_isalpha(next_char) || next_char == '_')
            result = ft_get_env_variable(input, env);
    else
    {
        result = ft_strdup("$");
        *input += 1;
    }
    return result;
}

//ok
char	*ft_get_env_variable(char **line, char **env)
{
    int		i;
    char	*key;
    char	*value;

    i = 0;
    *line += 1;  
    while ((*line)[i] && (ft_isalnum((*line)[i]) || (*line)[i] == '_'))
        i++;
    key = ft_substr(*line, 0, i);
    if (!key)
        return (NULL);
    value = ft_find_env_value(key, env);
    *line += i;
    free(key);
    return (value);
}


//ok
char *ft_get_arg_value(char **line, char **argv)
{
    int index = 0;
    int target_index;
    char *result;
    char *index_str;

    result = 0;
    *line += 1;
    index_str = ft_substr(*line, 0, 1);
    if (!index_str)
        return (NULL);
    target_index = atoi(index_str);
    while ((*argv)[index])
    {
        if (index == target_index)
        {
            result = ft_strdup(argv[index]);
            break;
        }
        index++;
    }
    *line += 1;
    free(index_str);
    return (result);
}


//ok
char	*ft_get_env_in_brackets(char **line, char **envp)
{
    char	*env;
    char	*temp;
    int		ret;

    (void) envp;
    ret = ft_isolate(line, &temp);
    if (!ret)
    {
        free(temp);
        ft_perror(0, temp, "not substitution");
        return (0);
    }
    env = ft_strtrim(temp, "${}");
    free(temp);
    temp = ft_find_env_value(env, envp);
    free(env);
    return (temp);
}
