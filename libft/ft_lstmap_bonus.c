/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:28:45 by larissa           #+#    #+#             */
/*   Updated: 2024/08/28 19:21:09 by larissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**aux;
	t_list	*tmp;
	t_list	*head;

	aux = &lst;
	head = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		tmp = ft_lstnew((*f)((*aux)->content));
		if (!tmp)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, tmp);
		lst = lst->next;
	}
	return (head);
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
    printf("\n");
}

void    ft_del_node(void *node)
{
    t_list    *tmp;

    if (node)
    {
        tmp = (t_list *)node;
        tmp->next = NULL;
        free(tmp->content);
        tmp->content = NULL;
    }
}

void* ft_toupper_int(void *ptr)
{
    char    *ptr_inter;
    size_t    i;
    char    *tmp;

    ptr_inter = (char *)ptr;
    tmp = ft_strdup(ptr_inter);

    i = 0;
    while(ptr_inter[i])
    {
        tmp[i] = ft_toupper(ptr_inter[i]);
        i++;
    }
    return ((void *)tmp);
}

int    main(void)
{
    char    *nbr00 = ft_strdup("A");
    char    *nbr01 = ft_strdup("bbbb");
    char    *nbr02 = ft_strdup("CCCcccCCC");
    t_list *head = NULL;
    t_list *ret;
    t_list *lstnbr00 = ft_lstnew(nbr00);
    t_list *lstnbr01 = ft_lstnew(nbr01);
    t_list *lstnbr02 = ft_lstnew(nbr02);
    printf("para lstnbr00: %p | %s\n", lstnbr00, nbr00);
    printf("para lstnbr01: %p | %s\n", lstnbr01, nbr01);
    printf("para lstnbr02: %p | %s\n", lstnbr02, nbr02);
    ft_lstadd_front(&head, lstnbr00);
    // ft_print_list(&head);
    ft_lstadd_front(&head, lstnbr01);
    // ft_print_list(&head);
    ft_lstadd_front(&head, lstnbr02);
    ft_print_list(&head);
    ret = ft_lstmap(head, ft_toupper_int, ft_del_node);
    printf("pré original\n");
    ft_print_list(&head);
    printf("pós original\n");
    printf("pré ret\n");
    ft_print_list(&ret);
    printf("pós ret\n");
    ft_lstclear(&head, ft_del_node);
    ft_lstclear(&ret, ft_del_node);
    printf("para head    : %p\n", head);
    printf("para ret     : %p\n", ret);
    return (0);
}
*/
