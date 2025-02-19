#include "../../include/minishell.h"

void	ft_update_var(char *key, char *value, t_env *env, char **update_pwd)
{
	int i;

	i = -1;
	while (env->var_list[++i])
	{
		if (ft_strncmp(env->var_list[i], key, ft_strlen(key)) == 0)
		{
			free(env->var_list[i]);
			env->var_list[i] = ft_strjoin(key, value);
			break;
		}
	}
	if (ft_srch_arr(env->var_list, key) != -1)
	{
		update_pwd[1] = ft_strjoin(key, value);
		ft_export(update_pwd, env);
		free(update_pwd[1]);
	}
}

void	ft_update_env(char *path, t_env *env)
{
	char	**update_pwd;

	if (!env || !env->var_list)
		return;
	update_pwd = malloc(sizeof(char *) * 3);
	if (!update_pwd)
		return;
	update_pwd[0] = ft_strdup("export ");
	update_pwd[2] = NULL;
	ft_update_var("OLDPWD=", env->pwd, env, update_pwd);
	free(env->pwd);
	if (path)
		env->pwd = ft_strdup(path);
	else
		env->pwd = ft_strdup("memes");
	ft_update_var("PWD=", env->pwd, env, update_pwd);
	ft_free_arr(update_pwd);
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
	}
}
