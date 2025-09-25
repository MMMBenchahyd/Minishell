/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:32 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:53:33 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	unsigned long	num;
	int				s;

	num = 0;
	s = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			s *= -1;
	while (*str >= '0' && *str <= '9')
	{
		if (num * 10 + *str - '0' > LONG_MAX)
		{
			return (-(s + 1) / 2);
		}
		num = num * 10 + *str++ - '0';
	}
	return ((int )num * s);
}
