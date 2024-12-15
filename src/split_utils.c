#include "minishell.h"

int is_space(int c)
{
    if (c == ' ' || c == '\t')
        return (c);
    return (0);
}

/*
Função: find_next_char

Descrição:
Encontra o próximo caractere de espaço ou o final da string,
a partir do índice fornecido, levando em consideração a
presença de aspas (simples ou duplas).

Parâmetros:
- char *str: A string onde será realizada a busca.
- int idx: O índice inicial para a busca.

Retorno:
- int: O índice do último caractere da palavra/frase encontrado
antes de espaço ou final da string, ou -1 se não encontrar
nenhum caractere relevante.
*/

int find_next_char(char *str, int idx)
{
    int flag;

    flag = 0;
    while (str[idx])
    {
		if ((str[idx] == 34 || str[idx] == 39) && flag == 0)
			flag = str[idx];
		else if (str[idx] == flag)
			flag = 0;
		if (is_space(str[idx]) && flag == 0)
            return (idx - 1);
		if ((!str[idx + 1]) && flag == 0)
			return (idx);
        idx++;
    }
    return (-1);
}

/*
Função: word_count

Descrição:
Conta o número de palavras em uma string,
ignorando espaços e tratando corretamente as palavras entre aspas.

Parâmetros:
- char *str: A string a ser analisada.

Retorno:
- size_t: O número de palavras encontradas na string.
*/

size_t  word_count(char *str)
{
    size_t  i;
    size_t  count;

    i = -1;
    count = 0;
    if (!str)
        return (0);
    while (str[++i])
    {
        if (!is_space(str[i]))
        {
            i = find_next_char(str, i);
            count++;
        }
    }
    return (count);
}

/*
Função: all_quotes_has_end

Descrição:
Verifica se todas as aspas (simples ou duplas) na string
possuem um par de fechamento correspondente.

Parâmetros:
- char *str: A string a ser verificada.

Retorno:
- int: NOTERROR (0) se todas as aspas têm um par de fechamento,
ou ERROR (1) se alguma aspa não tem fechamento.
*/

int all_quotes_has_end(char *str)
{
    int i;
    int flag;

    i = -1;
    flag = 0;
    while (str[++i])
    {
		if ((str[i] == 34 || str[i] == 39) && flag == 0)
			flag = str[i];
		else if (str[i] == flag)
			flag = 0;
    }
	if (flag == 0)
		return (NOTERROR);
	return (ERROR);
}

/*
void test_find_next_char() {
    char *str1 = "Hello World";
    printf("Teste 1: ");
    printf("Resultado esperado: 4, Resultado obtido: %d\n", find_next_char(str1, 0));

    char *str2 = "\"Hello \"World Test";
    printf("Teste 2: ");
    printf("Resultado esperado: 12, Resultado obtido: %d\n", find_next_char(str2, 0));

    char *str3 = "'Hello 'World' 'Test";
    printf("Teste 3: ");
    printf("Resultado esperado: 19, Resultado obtido: %d\n", find_next_char(str3, 0));

    char *str4 = "Hello   World";
    printf("Teste 4: ");
    printf("Resultado esperado: 4, Resultado obtido: %d\n", find_next_char(str4, 0));

    char *str5 = "Hello World ";
    printf("Teste 5: ");
    printf("Resultado esperado: 10, Resultado obtido: %d\n", find_next_char(str5, 6));

    char *str6 = "";
    printf("Teste 6: ");
    printf("Resultado esperado: -1, Resultado obtido: %d\n", find_next_char(str6, 0));

    char *str7 = "HelloWorld";
    printf("Teste 7: ");
    printf("Resultado esperado: 9, Resultado obtido: %d\n", find_next_char(str7, 0));

    char *str8 = "    ";
    printf("Teste 8: ");
    printf("Resultado esperado: -1, Resultado obtido: %d\n", find_next_char(str8, 0));

    char *str9 = "Hello World";
    printf("Teste 9: ");
    printf("Resultado esperado: 4, Resultado obtido: %d\n", find_next_char(str9, 2));

    char *str10 = "\"Hello World'\"";
    printf("Teste 10: ");
    printf("Resultado esperado: 13, Resultado obtido: %d\n", find_next_char(str10, 0));
}
*/
/*
void test_word_count() {
    char *str1 = "Hello";
    printf("Teste 1: ");
    printf("Resultado esperado: 1, Resultado obtido: %zu\n", word_count(str1));

    char *str2 = "Hello World";
    printf("Teste 2: ");
    printf("Resultado esperado: 2, Resultado obtido: %zu\n", word_count(str2));

    char *str3 = "Hello   World";
    printf("Teste 3: ");
    printf("Resultado esperado: 2, Resultado obtido: %zu\n", word_count(str3));

    char *str4 = "";
    printf("Teste 4: ");
    printf("Resultado esperado: 0, Resultado obtido: %zu\n", word_count(str4));

    char *str5 = "Hello World   ";
    printf("Teste 5: ");
    printf("Resultado esperado: 2, Resultado obtido: %zu\n", word_count(str5));

    char *str6 = "     ";
    printf("Teste 6: ");
    printf("Resultado esperado: 0, Resultado obtido: %zu\n", word_count(str6));

    char *str7 = "Hello  World Test";
    printf("Teste 7: ");
    printf("Resultado esperado: 3, Resultado obtido: %zu\n", word_count(str7));

    char *str8 = "    Hello    World    Test    ";
    printf("Teste 8: ");
    printf("Resultado esperado: 3, Resultado obtido: %zu\n", word_count(str8));

    char *str9 = "Hello, World! Test.";
    printf("Teste 9: ");
    printf("Resultado esperado: 3, Resultado obtido: %zu\n", word_count(str9));

    char *str10 = "Hello 'World' Test";
    printf("Teste 10: ");
    printf("Resultado esperado: 3, Resultado obtido: %zu\n", word_count(str10));

    char *str11 = "This is  a  test    string.";
    printf("Teste 11: ");
    printf("Resultado esperado: 5, Resultado obtido: %zu\n", word_count(str11));
}
*/
/*
int main() {
//    test_find_next_char();
    test_word_count();
    return 0;
}
*/