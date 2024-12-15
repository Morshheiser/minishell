#include "minishell.h"

/*
Função: word_between_spaces

Descrição:
Extrai uma palavra de uma string a partir de um índice fornecido,
retornando a palavra até o próximo espaço ou o final da string.

Parâmetros:
- char *str: A string de onde a palavra será extraída.
- int idx: O índice inicial da palavra na string.

Retorno:
- char *: A palavra extraída, ou NULL se não for possível extrair.

Observação:
A memória alocada para a palavra deve ser liberada com `free()` após o uso.
*/

char	*word_between_spaces(char *str, int idx)
{
    int     wlen;
    int     end_word;
    int     iret;
    char    *ret;

    iret = -1;
    end_word = find_next_char(str, idx);
    if (end_word == -1)
        return (NULL);
    wlen = (end_word - idx) + 1;
    ret = (char *) malloc((wlen + 1) * sizeof(char));
    if (!ret)
        return (NULL);
    while (++iret < wlen)
        ret[iret] = str[idx++];
    printf("idx iret: %d - idx str: %d\n", iret, idx);
    ret[iret] = '\0';
    return (ret);
}

void	split_free(char **str, size_t o)
{
	size_t	i;

	i = 0;
	while (i < o)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/*
 Função: mod_split_input
 
 Descrição:
 Divide uma string em palavras, retornando um vetor de strings.
 Ignora espaços extras e separa as palavras corretamente. O vetor é
 terminado com um ponteiro NULL.
 
 Parâmetros:
 - char *str: A string de entrada a ser dividida.
 
 Retorno:
 - char **: Vetor de palavras extraídas da string, terminado com NULL.
            Retorna NULL em caso de erro.
 
 Observação:
 A memória alocada para o vetor de palavras e para cada palavra extraída
 deve ser liberada com `free()` após o uso.
*/


char    **mod_split_input(char *str)
{
    int     istr;
    int     iret;
    char    **ret;

    istr = 0;
    iret = 0;
    if (!str)
        return (NULL);
    ret = (char **) ft_calloc(word_count(str) + 1, sizeof(char *));
    if (!ret)
        return (NULL);
    while (ret && str[istr])
    {
        if (!is_space(str[istr]))
        {
            ret[iret] = word_between_spaces(str, istr);
            if (!ret[iret])
            {
                split_free(ret, iret);
                return (NULL);
            }
            istr = find_next_char(str, istr);
            iret++;
        }
        istr++;
    }
    ret[iret] = NULL;
    return (ret);
}

/*
void test_word_between_spaces(void)
{
    char *str1 = "Este é um exemplo de string.";
    char *str2 = "Palavra com acento: café!";
    char *str3 = "   Início com espaço";
    char *str4 = "Fim com espaço  ";
    char *str5 = "Teste de palavra única";
    char *str6 = "    ";

    printf("\nTeste 1: Palavra no meio da string\n");
    char *word1 = word_between_spaces(str1, 5);
    if (word1)
    {
        printf("Palavra extraída: '%s'|\n", word1);
        free(word1);
    }

    printf("\nTeste 2: Palavra com acento\n");
    char *word2 = word_between_spaces(str2, 20);
    if (word2) {
        printf("Palavra extraída: '%s'|\n", word2);
        free(word2);
    }

    printf("\nTeste 3: Palavra no início da string\n");
    char *word3 = word_between_spaces(str3, 3);
    if (word3) {
        printf("Palavra extraída: '%s'|\n", word3);
        free(word3);
    }

    printf("\nTeste 4: Palavra no final da string\n");
    char *word4 = word_between_spaces(str4, 0);
    if (word4) {
        printf("Palavra extraída: '%s'|\n", word4);
        free(word4);
    }

    printf("\nTeste 5: Palavra de apenas 1 caractere\n");
    char *word5 = word_between_spaces(str5, 0);
    if (word5) {
        printf("Palavra extraída: '%s'|\n", word5);
        free(word5);
    }

    printf("\nTeste 6: String com apenas espaços\n");
    char *word6 = word_between_spaces(str6, 4);
    if (word6) {
        printf("Palavra extraída: '%s'|\n", word6);
        free(word6);
    } else {
        printf("Nenhuma palavra extraída\n");
    }
}
*/
/*
void test_mod_split_input(void)
{
    char *str1 = "Este é um exemplo";
    printf("\nTeste 1: String com palavras separadas por um único espaço\n");
    char **result1 = mod_split_input(str1);
    if (result1)
    {
        for (int i = 0; result1[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result1[i]);
            free(result1[i]);
        }
        free(result1);
    }

    char *str2 = "Texto  com   múltiplos    espaços";
    printf("\nTeste 2: String com múltiplos espaços\n");
    char **result2 = mod_split_input(str2);
    if (result2)
    {
        for (int i = 0; result2[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result2[i]);
            free(result2[i]);
        }
        free(result2);
    }
    char *str3 = "";//pode colocar um '\0';
    printf("\nTeste 3: String vazia\n");
    char **result3 = mod_split_input(str3);
    if (result3 == NULL || result3[0] == NULL)
    {
        printf("Resultado esperado: NULL (sem palavras)\n");
    }
    else
    {
        for (int i = 0; result3[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result3[i]);
            free(result3[i]);
        }
        free(result3);
    }

    char *str4 = "   Início e fim com espaços   ";
    printf("\nTeste 4: String com espaços no início e no final\n");
    char **result4 = mod_split_input(str4);
    if (result4)
    {
        for (int i = 0; result4[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result4[i]);
            free(result4[i]);
        }
        free(result4);
    }

    char *str5 = "Palavra1 Palavra2";
    printf("\nTeste 5: String com apenas um espaço no meio\n");
    char **result5 = mod_split_input(str5);
    if (result5)
    {
        for (int i = 0; result5[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result5[i]);
            free(result5[i]);
        }
        free(result5);
    }

    char *str6 = "Café é bom!";
    printf("\nTeste 6: String com caracteres especiais (acentos, pontuação)\n");
    char **result6 = mod_split_input(str6);
    if (result6)
    {
        for (int i = 0; result6[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result6[i]);
            free(result6[i]);
        }
        free(result6);
    }

    char *str7 = "     ";
    printf("\nTeste 7: String composta apenas por espaços\n");
    char **result7 = mod_split_input(str7);
    if (result7 == NULL || result7[0] == NULL)
    {
        printf("Resultado esperado: NULL (sem palavras)\n");
    }
    else
    {
        for (int i = 0; result7[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result7[i]);
            free(result7[i]);
        }
        free(result7);
    }

    char *str8 = "Supercalifragilisticexpialidocious exemplo";
    printf("\nTeste 8: String com palavras grandes\n");
    char **result8 = mod_split_input(str8);
    if (result8)
    {
        for (int i = 0; result8[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result8[i]);
            free(result8[i]);
        }
        free(result8);
    }

    char *str9 = NULL;
    printf("\nTeste 9: Ponteiro NULL como entrada\n");
    char **result9 = mod_split_input(str9);
    if (result9 == NULL)
    {
        printf("Resultado esperado: NULL (entrada NULL)\n");
    }

    char *str10 = "UmaPalavra";
    printf("\nTeste 10: String com apenas uma palavra\n");
    char **result10 = mod_split_input(str10);
    if (result10)
    {
        for (int i = 0; result10[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result10[i]);
            free(result10[i]);
        }
        free(result10);
    }

    char *str11 = "!";
    printf("\nTeste 10: String com apenas um char\n");
    char **result11 = mod_split_input(str11);
    if (result11)
    {
        for (int i = 0; result10[i] != NULL; i++)
        {
            printf("Palavra %d: '%s'|\n", i + 1, result11[i]);
            free(result11[i]);
        }
        free(result11);
    }
}
*/
/*
int main() {
    //test_word_between_spaces();
    test_mod_split_input();
    return (0);
}
*/