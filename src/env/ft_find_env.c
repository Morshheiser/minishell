#include "../../include/minishell.h"

char	*ft_get_env(char *key, char **env)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (NULL);
	i = -1;
	key_len = ft_strlen(key);
	while (env[++i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 &&
			(key[key_len - 1] == '=' || env[i][key_len] == '='))
			return (env[i]);
	}
	return (NULL);
}