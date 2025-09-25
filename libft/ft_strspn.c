/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:54:57 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/13 01:17:09 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strspn(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i])
	{
		if (!ft_strchr(str1[i], str2))
			break ;
		i++;
	}
	return (i);
}
