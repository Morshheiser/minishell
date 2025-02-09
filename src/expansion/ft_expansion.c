#include "../../include/minishell.h"

char	*ft_expand_variables(char *input, char **args, char **env)
{
	char	*result;
	char	*temp;

	if (!input)
		return (NULL);

	// Inicialização do resultado final
	result = NULL;
	while (*input)
	{
		// Debug: Mostrar o caractere atual sendo analisado
		printf("Analisando caractere: '%c'\n", *input);

		if (*input == '$') // Se o caractere for '$'
		{
			// Debug: Entrando na expansão de variável de ambiente
			printf("Detectado '$'. Expansão de variável de ambiente.\n");
			temp = ft_expand_env_variable(&input, args, env);
		}
		else if (*input == '\"') // Se o caractere for aspas duplas
		{
			// Debug: Entrando na expansão de aspas duplas
			printf("Detectado '\"'. Expansão de aspas duplas.\n");
			temp = ft_expand_double_quotes(&input, args, env);
		}
		else if (*input == '\'') // Se o caractere for aspas simples
		{
			// Debug: Entrando na expansão de aspas simples
			printf("Detectado '\''. Expansão de aspas simples.\n");
			temp = ft_expand_single_quotes(&input);
		}
		else // Caso contrário, é texto simples
		{
			// Debug: Expansão de texto simples
			printf("Texto simples detectado.\n");
			temp = ft_expand_plain_text(&input, "$'\"");
		}

		// Debug: Mostrar o resultado da expansão de cada parte
		printf("Resultado da expansão: '%s'\n", temp);

		// Mesclando a string resultante com a nova parte
		result = ft_merge_strings(result, temp);
		if (!result)
		{
			// Se ocorrer um erro ao mesclar, retornamos NULL
			printf("Erro ao mesclar strings.\n");
			return (NULL);
		}

		// Debug: Exibir o estado atual de 'result' após mesclar
		printf("Estado atual do resultado: '%s'\n", result);
	}

	// Resultado final após expandir todas as variáveis
	printf("Resultado final da expansão: '%s'\n", result);
	return (result);
}
