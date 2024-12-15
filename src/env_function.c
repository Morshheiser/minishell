#include "minishell.h"

static int	first_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

t_env	*new_env_lst(char **ev, t_env *env_list)
{
	int		i;
	int		equal_index;
	char	*key;
	char	*str;
	t_env	*new;

	i = -1;
	while (ev[++i])
	{
		equal_index = first_equal(ev[i]);
		key = ft_substr(ev[i], 0, equal_index);
		if (!key)
			return (NULL);
		str = ft_substr(ev[i], equal_index + 1, strlen(ev[i]) - equal_index - 1);
		if (!str)
		{
			free (key);
			return (NULL);
		}
		new = my_lstnew(key, str);
		//fazer tratamento caso dê errado
		my_lstadd_back(&env_list, new);
	}
	return (env_list);
}
/*
int main(int ac, char **av, char **ev)
{
	int i = -1;
    t_env *tmp;
	t_env *env_list;
    env_list = NULL;

    env_list = new_env_lst(ev, env_list);

    tmp = env_list;
    while (ev[++i])
        printf("String do env: %s\n\n", ev[i]);
    printf("----------------------------------------\n");
    while (tmp)
    {
        printf("Str da struct: %s\n", tmp->key);
        printf("Frase da struct: %s\n\n", tmp->str);
        tmp = tmp->next;
    }

    free_env(env_list);
	return (0);
}
*/
