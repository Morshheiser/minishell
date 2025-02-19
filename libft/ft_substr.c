/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:18:50 by penascim          #+#    #+#             */
/*   Updated: 2025/02/18 20:16:17 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = ft_strlen(s);
	if (start > i)
		start = i;
	if (len > (i - start))
		len = (i - start);
	str = malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (len --)
		*(str + i++) = *(s + start++);
	*(str + i) = '\0';
	return (str);
}