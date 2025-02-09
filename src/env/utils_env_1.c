#include "../../include/minishell.h"

char **ft_arr_copy(char **arr, int size)
{
    int i;
    int len;
    char **arr_cpy;

    if (!arr) {
        printf("[DEBUG] ft_arr_copy: O array de entrada é NULL.\n");
        return (NULL);
    }
    i = 0;
    len = 0;
    while (arr[len]) {
        len++;
    }
    printf("[DEBUG] ft_arr_copy: Tamanho do array de entrada: %d\n", len);

    arr_cpy = malloc(sizeof(char *) * (len + 1 + size));
    if (!arr_cpy) {
        printf("[DEBUG] ft_arr_copy: Erro ao alocar memória para o array de cópia.\n");
        return (NULL);
    }
    printf("[DEBUG] ft_arr_copy: Memória alocada com sucesso para o array de cópia.\n");

    while (i < len && arr[i]) {
        arr_cpy[i] = ft_strdup(arr[i]);
        printf("[DEBUG] ft_arr_copy: Copiando elemento %d: %s\n", i, arr_cpy[i]);
        i++;
    }

    // Preenchendo com NULL após o conteúdo copiado
    while (i < len + size) {
        arr_cpy[i] = NULL;
        i++;
    }

    printf("[DEBUG] ft_arr_copy: Cópia do array concluída.\n");
    return (arr_cpy);
}

int ft_size(char **arr)
{
    int len;

    len = 0;
    if (!arr) {
        printf("[DEBUG] ft_size: O array é NULL.\n");
        return (len);
    }

    while (arr[len]) {
        len++;
    }

    printf("[DEBUG] ft_size: Tamanho do array: %d\n", len);
    return (len);
}

int ft_srch_arr(char **array, char *str)
{
    int i;
    int len;

    if (!array || !str) {
        printf("[DEBUG] ft_srch_arr: O array ou a string de pesquisa são NULL.\n");
        return (-1);
    }
    
    len = ft_strlen(str);
    printf("[DEBUG] ft_srch_arr: Procurando pela string '%s' de comprimento %d.\n", str, len);
    i = 0;
    
    while (array[i]) {
        if (!ft_strncmp(array[i], str, len) && array[i][len] == '=') {
            printf("[DEBUG] ft_srch_arr: Encontrado '%s' no índice %d.\n", array[i], i);
            return (i);
        }
        i++;
    }

    printf("[DEBUG] ft_srch_arr: A string '%s' não foi encontrada.\n", str);
    return (-1);
}

long long int ft_atolli(const char *str)
{
    long long int result;
    int sign;
    int i;

    i = 0;
    result = 0;
    sign = 1;

    // Ignorando espaços em branco
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ') {
        i++;
    }

    if (str[i] == '-') {
        sign *= -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    printf("[DEBUG] ft_atolli: Processando número a partir de: '%s'\n", &str[i]);

    while (ft_isdigit(str[i])) {
        result *= 10;
        result += sign * (str[i] - '0');
        printf("[DEBUG] ft_atolli: Resultado atual: %lld, caractere: '%c'\n", result, str[i]);
        i++;
    }

    printf("[DEBUG] ft_atolli: Valor final convertido: %lld\n", result);
    return (result);
}
