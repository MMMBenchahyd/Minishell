/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:54:22 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:54:23 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	f_dlmt(char c, char s)
{
	if (s == c && s)
		return (1);
	return (0);
}

static int	ft_sstrlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s && !f_dlmt(*s, c))
	{
		i++;
		s++;
	}
	return (i);
}

int	count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!f_dlmt(s[i], c) && f_dlmt(s[i + 1], c))
			count++;
		i++;
	}
	if (i && !f_dlmt(s[--i], c))
		count++;
	return (count);
}

static char	*ft_strdupn(char const **s, char c)
{
	int		size;
	char	*ptr;
	int		i;

	i = 0;
	while (f_dlmt(**s, c))
		*s += 1;
	size = ft_sstrlen(*s, c);
	ptr = (char *)ft_malloc(size + 1);
	while (**s && !f_dlmt(**s, c))
	{
		ptr[i++] = **s;
		*s += 1;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	char	**ptr;

	i = 0;
	if (!s || !*s)
		return (NULL);
	words = count_word(s, c);
	ptr = (char **)ft_malloc(sizeof(char *) * (words + 1));
	while (i < words)
		ptr[i++] = ft_strdupn(&s, c);
	ptr[i] = 0;
	return (ptr);
}
