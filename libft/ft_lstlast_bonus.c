/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:50:07 by larissa           #+#    #+#             */
/*   Updated: 2024/08/28 19:20:54 by larissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
# include <stdio.h>    
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
    int        nbr00 = 21;
    int        nbr01 = 42;
    int        nbr02 = 84;
    t_list *head = NULL;
    t_list *lstnbr00 = ft_lstnew(&nbr00);
    t_list *lstnbr01 = ft_lstnew(&nbr01);
    t_list *lstnbr02 = ft_lstnew(&nbr02);
    t_list *lstlast = NULL;
    printf("para lstnbr00: %p\n", lstnbr00);
    printf("para lstnbr01: %p\n", lstnbr01);
    printf("para lstnbr02: %p\n", lstnbr02);
    ft_lstadd_front(&head, lstnbr00);
    ft_print_list(&head);
    ft_lstadd_front(&head, lstnbr01);
    ft_print_list(&head);
    ft_lstadd_front(&head, lstnbr02);
    ft_print_list(&head);
    lstlast = ft_lstlast(head);
    printf("Último ponteiro: %p | ", lstlast);
    printf("conteúdo: %i\n", *((int *)((lstlast)->content)));
    ft_free_list(&head);
    return (0);
}
*/
