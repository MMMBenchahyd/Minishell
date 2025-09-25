/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:54:27 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:54:28 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	ptr1;
	unsigned char	ptr2;

	i = 0;
	while (s1[i] || s2[i])
	{
		ptr1 = (unsigned char)s1[i];
		ptr2 = (unsigned char)s2[i];
		if (ptr1 != ptr2)
			return ((int)(ptr1 - ptr2));
		i++;
	}
	return (0);
}
