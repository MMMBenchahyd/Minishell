/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envstr_to_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:51:47 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:51:47 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	extract_key_and_value(char *str, char **key,
									char **equal, char **value)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '=' || !ft_strncmp(ptr, "+=", 2))
			break ;
		ptr++;
	}
	*key = ft_xtract_env(str, ptr);
	if (!ft_strncmp(ptr, "+=", 2))
	{
		*equal = ft_xtract_env(ptr, ptr + 2);
		ptr += 2;
	}
	else if (*ptr == '=')
	{
		*equal = ft_xtract_env(ptr, ptr + 1);
		ptr += 1;
	}
	*value = ft_xtract_env(ptr, ptr + ft_strlen(ptr));
}

t_env	*ft_envstr_to_lst(char *str)
{
	char	*key;
	char	*equal;
	char	*value;

	equal = NULL;
	value = NULL;
	if (!str)
		return (NULL);
	extract_key_and_value(str, &key, &equal, &value);
	return (ft_lstnew_env(key, equal, value));
}
