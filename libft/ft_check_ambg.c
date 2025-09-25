/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ambg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:40 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:53:40 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_c_word(char *str, char *delimiters)
{
	size_t	i;
	int		word_count;
	int		in_word;

	i = 0;
	word_count = 0;
	in_word = 0;
	while (str[i])
	{
		if (!ft_strchr(str[i], delimiters))
		{
			if (!in_word)
			{
				word_count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		if (word_count > 1)
			return (1);
		i++;
	}
	return (word_count > 1);
}

int	check_ambg(char *str, char *delimiters)
{
	char	*ptr;

	ptr = ft_getenv(str + 1);
	if (ptr)
		return (check_c_word(ptr, delimiters));
	return (1);
}
