/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:51:27 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:51:27 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_envchr(char *key)
{
	t_env	*tmp;

	tmp = *ft_env_head();
	while (tmp)
	{
		if (!tmp->key)
		{
			tmp = tmp->next;
			continue ;
		}
		if (!ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_valid_env_key(char *key)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(key[0]) || key[0] == '_')
	{
		while (key[i])
		{
			if (!ft_isalnum(key[i]) && key[i] != '_')
				break ;
			i++;
		}
		if (key[i] == 0)
			return (1);
	}
	return (0);
}
