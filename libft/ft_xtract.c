/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtract.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:01 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:55:02 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_xtract(const char *start, const char *end)
{
	int		len;
	int		i;
	char	*ptr;

	len = end - start;
	i = 0;
	ptr = ft_malloc(len + 1);
	while (i < len)
		ptr[i++] = *start++;
	ptr[i] = '\0';
	return (ptr);
}
