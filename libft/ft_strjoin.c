/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:15:26 by penascim          #+#    #+#             */
/*   Updated: 2025/02/10 13:42:31 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
    size_t len;
    size_t i = 0;
    size_t j = 0;
    char *newstr;


    if (!s1)
        s1 = "";
    if (!s2)
        s2 = "";
    len = ft_strlen(s1) + ft_strlen(s2);
    newstr = malloc(sizeof(char) * (len + 1));
    if (!newstr)
        return ((void *)0);
    if (s1)
	{
    	while (s1[i] != '\0')
    	{
    	    newstr[i] = s1[i];
        	i++;
    	}
	}
	if (s2)
	{
    	while (s2[j] != '\0')
    	{
        	newstr[i] = s2[j];
        	i++;
        	j++;
    	}
	}
    newstr[i] = '\0';
    return newstr;
}
