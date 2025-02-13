#include "../../../include/minishell.h"

void	ft_update_env(char *path, t_env *env)
{
	int		i;

	if (!env || !env->var_list)
		return ;
	i = -1;
	while (env->var_list[++i])
	{
		if (ft_strncmp(env->var_list[i], "OLDPWD=", 7) == 0)
		{
			free(env->var_list[i]);
			env->var_list[i] = ft_strjoin("OLDPWD=", env->pwd);
			break ;
		}
	}
	if (env->pwd)
		free(env->pwd);
	if (path)
		env->pwd = ft_strdup(path);
	else
		env->pwd = ft_strdup("memes");
	i = -1;
	while (env->var_list[++i])
	{
		if (ft_strncmp(env->var_list[i], "PWD=", 4) == 0)
		{
			free(env->var_list[i]);
			env->var_list[i] = ft_strjoin("PWD=", env->pwd);
			break ;
		}
	}
}

void	ft_follow_path(char *path, t_env *env)
{
	char *home_path;
	char *oldpwd_path;

	if (!path || !ft_strncmp(path, "~", 2))
	{
		home_path = ft_get_env("HOME", env->var_list);
		if (chdir(home_path + 5))
		{
			printf("cd: HOME not set\n");
			status_g = 1;
			return ;
		}
	}
	else if (!ft_strncmp(path, "-", 2))
	{
		oldpwd_path = ft_get_env("OLDPWD", env->var_list);
		if (!oldpwd_path || chdir(oldpwd_path + 7))
		{
			printf("cd: OLDPWD not set\n");
			status_g = 1;
			return ;
		}
	}
	else if (chdir(path))
	{
		printf("cd: %s: No such file or directory\n", path);
		status_g = 1;
		return ;
	}
}

void	ft_cd(char **args, t_env *env)
{
	char	*path;

	status_g = 0;
	if (ft_size(args) > 2)
	{
		printf("cd: too many arguments\n");
		status_g = 1;
		return ;
	}
	ft_follow_path(args[1], env);
	if (!status_g)
	{
		path = getcwd(NULL, 0);
		if (!path)
		{
			printf("cd: failed to retrieve the current directory: "
				"getcwd: cannot access parent directories\n");
			return ;
		}
		ft_update_env(path, env);
		if(path)
			free(path);
	}
}
