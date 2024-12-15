/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:42:28 by larissa           #+#    #+#             */
/*   Updated: 2024/08/28 19:21:21 by larissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *) malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
/*
#include <stdio.h>
int    main(void)
{
    int        nbr = 42;
    char    str[42] = "42Rio";
    t_list *lstnbr = ft_lstnew(&nbr);
    t_list *lststr = ft_lstnew(str);

    printf("para nbr: %i\t| ", nbr);
    printf("para lstnbr: %i\n", *((int *)(lstnbr->content)));
    printf("para str: %s\t| ", str);
    printf("para lststr: %s\n", ((char *)(lststr->content)));

    free(lstnbr);
    lstnbr = NULL;
    free(lststr);
    lststr = NULL;
    return (0);
}
*/
