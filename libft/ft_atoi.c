/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:41:09 by ukim              #+#    #+#             */
/*   Updated: 2021/06/14 13:31:39 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
 
static int	is_space(int c)
{
	if (c == ' ' ||
		c == '\n' ||
		c == '\t' ||
		c == '\v' ||
		c == '\f' ||
		c == '\r')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	if (num > LLONG_MAX)
		return (sign == 1 ? -1 : 0);
	return (sign * num);
}
