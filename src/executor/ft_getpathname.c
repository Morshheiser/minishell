#include "../../include/minishell.h"

char *ft_get_path_name(char *cmd, t_env *env_list)
{
    char *full_path;
    char *env_path;

    if (!cmd || !env_list)
        return NULL;
    full_path = NULL;
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK | X_OK))
			status_g = ft_perror(126 + (errno == 2), cmd, 0);
		else
			full_path = ft_strdup(cmd);
    }
    else
    {
        env_path = ft_find_env_value("PATH", env_list->var_list);
        if (!env_path)
        {
            status_g = ft_perror(127, cmd, "ft_get_path_name: Caminho não encontrado no PATH\n");
            return NULL;
        }
        full_path = ft_find_relative(cmd, env_path);
        free(env_path);
    }
    return full_path;
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

