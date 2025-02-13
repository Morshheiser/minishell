/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penascim <penascim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:36:52 by penascim          #+#    #+#             */
/*   Updated: 2024/04/08 19:55:57 by penascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// long	ft_atoi(const char *ptr)
// {
// 	long	result;
// 	int		signal;

// 	result = 0;
// 	signal = 1;
// 	while ((*ptr == 32) || (*ptr >= 9 && *ptr <= 13))
// 		ptr++;
// 	if (*ptr == '-' || *ptr == '+')
// 	{
// 		if (*ptr == '-')
// 			signal = -1;
// 		ptr++;
// 	}
// 	while (*ptr >= '0' && *ptr <= '9')
// 	{
// 		result *= 10;
// 		result += *ptr++ - '0';
// 	}
// 	return ((long)(result * signal));
// }
/*
#include <stdio.h>

int	main(void)
{
	printf("%ld", ft_atoi("2147483649"));
}
*/
