#include "../../include/minishell.h"
void	ft_end(t_env *env, t_shell *shell)
{
	if(!env || !shell)
		return ;
	ft_clean_sh(shell);
	ft_free_arr(env->var_list);
	free(env->pwd);
	free(env);
}

int ft_compare_with_limit(char *arg, int i, int len, int sign)
{
    char *limit;
    int j;

    if (sign == 1)
		limit = "9223372036854775807";
    else
		limit = "9223372036854775808";
    j = 0;
    while (j < len)
    {
        if (arg[i + j] > limit[j])
            return 1;
        if (arg[i + j] < limit[j])
            return 0;
		j++;
    }
    return 0;
}
//rever 
int ft_is_overflow(char *arg)
{
    int sign;
    int i;
    int len;

    i = 0;
    sign = 1;
    if (arg[i] == '-' || arg[i] == '+')
    {
        if (arg[i] == '-')
            sign = -1;
        i++;
    }
    while (arg[i] == '0')
        i++;
    if (arg[i] == '\0')
        return 0;
    len = ft_strlen(arg + i);
    if (len > 19)
        return 1;
    return (ft_compare_with_limit(arg, i, len, sign));
}

int	ft_is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (1);
    }
	return (0);
}

void	ft_exit(char **args, t_env *env, t_shell *shell)
{
	unsigned char	ret;

//!! Por que esse status_g se está apagando as funções de variável global?
	status_g = 0;
//------------------------------------------------------------------------
	printf("exit\n");
	if (ft_size(args) == 2)
	{
		if (ft_is_all_digit(args[1]) || ft_is_overflow(args[1]))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			status_g = 2;
		}
		else
		{
			ret = ft_atolli(args[1]);
			status_g = ret;
		}
	}
	else if (ft_size(args) > 2)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	ft_end(env, shell);
	exit(status_g);
}
