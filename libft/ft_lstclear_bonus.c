/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:38:46 by larissa           #+#    #+#             */
/*   Updated: 2024/08/28 19:20:01 by larissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	if (!lst || !del)
		return ;
	aux = *lst;
	while (aux)
	{
		aux = (*lst)->next;
		ft_lstdelone((*lst), del);
		(*lst) = aux;
	}
	*lst = NULL;
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
	printf("conteúdo: %s\n", ((char *)((tmp)->content)));
        tmp = tmp->next;
    }
}

void    ft_del_node(void *node)
{
    t_list *aux;

    aux = (t_list *)node;
    if (aux->content)
    {
        free(aux->content);
        aux->content = NULL;
    }
    aux->next = NULL;
    aux = NULL;
}

// void    ft_del_node(void *node)
// {
//     t_list    *tmp;

//     if (node)
//     {
//         tmp = (t_list *)node;
//         tmp->next = NULL;
//         free(tmp->content);
//         tmp->content = NULL;
//     }
// }

int    main(void)
{
    char    *nbr00 = ft_strdup("21");
    char    *nbr01 = ft_strdup("42");
    char    *nbr02 = ft_strdup("84");
    t_list *head = NULL;
    t_list *lstnbr00 = ft_lstnew(nbr00);
    t_list *lstnbr01 = ft_lstnew(nbr01);
    t_list *lstnbr02 = ft_lstnew(nbr02);
    printf("para lstnbr00: %p | %s\n", lstnbr00, nbr00);
    printf("para lstnbr01: %p | %s\n", lstnbr01, nbr01);
    printf("para lstnbr02: %p | %s\n", lstnbr02, nbr02);
    ft_lstadd_front(&head, lstnbr00);
    ft_print_list(&head);
    ft_lstadd_front(&head, lstnbr01);
    ft_print_list(&head);
    ft_lstadd_front(&head, lstnbr02);
    ft_print_list(&head);
    ft_lstclear(&head, ft_del_node);
    printf("para head    : %p\n", head);
    return (0);
}
*/
