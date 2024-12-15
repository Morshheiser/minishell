/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:37:31 by larissa           #+#    #+#             */
/*   Updated: 2024/08/28 19:20:18 by larissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst);
	free(lst);
}
/*
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
    printf("\n");
}

//void    ft_del_node(void *node)
//{
//    t_list    *tmp;
//
//    tmp = (t_list *)node;
//    tmp->next = NULL;
//    free(tmp->content);
//    tmp->content = NULL;
//}

void    ft_free_list(t_list **head)
{
    t_list *tmp = *head;

    while (tmp)
    {
        tmp = (*head)->next;
        ft_lstdelone(*head, &ft_del_node);
        *head = tmp;
    }
}

int    main(void)
{
    char    *nbr00 = ft_strdup("21");
    char    *nbr01 = ft_strdup("42");
    char    *nbr02 = ft_strdup("84");
    t_list *head = NULL;
    t_list *lstnbr00 = ft_lstnew(nbr00);
    t_list *lstnbr01 = ft_lstnew(nbr01);
    t_list *lstnbr02 = ft_lstnew(nbr02);
    printf("para lstnbr00: %p |, lstnbr00);
    printf("%s\n", nbr00);
    printf("para lstnbr01: %p |, lstnbr001);
    printf("%s\n", nbr01);
    printf("para lstnbr02: %p |, lstnbr002);
    printf("%s\n", nbr02);
    ft_lstadd_front(&head, lstnbr00);
    ft_print_list(&head);
    ft_lstadd_front(&head, lstnbr01);
    ft_print_list(&head);
    ft_lstadd_front(&head, lstnbr02);
    ft_print_list(&head);
    ft_free_list(&head);
    return (0);
}
*/
