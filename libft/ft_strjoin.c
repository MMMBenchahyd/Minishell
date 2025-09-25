/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:54:34 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:54:35 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	char	*ptr;
	size_t	slen1;
	size_t	slen2;

	slen1 = 0;
	slen2 = 0;
	if (s1 != NULL)
		slen1 = ft_strlen(s1);
	if (s2 != NULL)
		slen2 = ft_strlen(s2);
	p = (char *)ft_malloc(slen2 + slen1 + 1);
	ptr = p;
	while (s1 != NULL && *s1)
		*p++ = *s1++;
	while (s2 != NULL && *s2)
		*p++ = *s2++;
	*p = '\0';
	return (ptr);
}
