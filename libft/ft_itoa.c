/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:54:02 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:54:03 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*nm_to_allo(char *nm, int nb)
{
	char	*ptr;
	int		i;

	i = nb;
	ptr = (char *)ft_malloc(nb);
	if (!ptr)
		return (NULL);
	if (*nm == '-')
	{
		*ptr++ = '-';
		i--;
	}
	while (*nm)
		nm++;
	while (--i)
		*ptr++ = *(--nm);
	*ptr = '\0';
	return (ptr - nb + 1);
}

char	*ft_itoa(int n)
{
	int		i;
	char	nm[15];

	i = 0;
	if (!n)
		return (nm_to_allo("0", 2));
	if (n == -2147483648)
		return (nm_to_allo("-8463847412", 12));
	if (n < 0)
	{
		n *= -1;
		nm [i++] = '-';
	}
	while (n)
	{
		nm [i++] = n % 10 + '0';
		n /= 10;
	}
	nm[i] = '\0';
	return (nm_to_allo(nm, i + 1));
}
