/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:54:44 by larissa           #+#    #+#             */
/*   Updated: 2024/08/28 19:19:09 by larissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	if (lst)
	{
		if (!(*lst))
			*lst = new;
		else
		{
			aux = ft_lstlast(*lst);
			aux->next = new;
		}
	}
}
/*
#include <stdio.h>
void    ft_print_list(t_list **head)
{
    t_list *tmp = *head;
    int        i    = 0;

    while (tmp)
    {
        printf("i: %i | ponteiro: %p | ", i++, tmp);
	printf("conteúdo: %i\n", *((int *)((tmp)->content)));
        tmp = tmp->next;
    }
    printf("\n");
}

void    ft_free_list(t_list **head)
{
    t_list *tmp = *head;

    while (tmp)
    {
        tmp = (*head)->next;
        (*head)->next = NULL;
        (*head)->content = NULL;
        free(*head);
        *head = tmp;
    }
}

int    main(void)
{
    t_list *head = NULL;
    {
        printf("Cenário 00\n");
        int        nbr00 = 21;
        int        nbr01 = 42;
        int        nbr02 = 84;
        t_list *lstnbr00 = ft_lstnew(&nbr00);
        t_list *lstnbr01 = ft_lstnew(&nbr01);
        t_list *lstnbr02 = ft_lstnew(&nbr02);
        printf("para lstnbr00: %p\n", lstnbr00);
        printf("para lstnbr01: %p\n", lstnbr01);
        printf("para lstnbr02: %p\n", lstnbr02);
        ft_lstadd_back(&head, lstnbr00);
        ft_print_list(&head);
        ft_lstadd_back(&head, lstnbr01);
        ft_print_list(&head);
        ft_lstadd_back(&head, lstnbr02);
        ft_print_list(&head);
        ft_free_list(&head);
    }
    {
        printf("Cenário 01\n");
        int        nbr00 = 21;
        t_list *lstnbr00 = ft_lstnew(&nbr00);
        printf("para ft_lstadd_back(NULL, lstnbr00)\n");
        ft_lstadd_back(NULL, lstnbr00);
        ft_print_list(&head);
        ft_free_list(&head);
        ft_free_list(&lstnbr00);
    }
    {
        printf("Cenário 02\n");
        printf("para ft_lstadd_back(&head, NULL)\n");
        ft_lstadd_back(&head, NULL);
        ft_print_list(&head);
        ft_free_list(&head);
    }
    return (0);
}
*/
