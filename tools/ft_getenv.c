/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:04 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:53:05 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *str)
{
	t_env	*env;

	env = *ft_env_head();
	while (env && ft_strcmp(str, env->key))
		env = env->next;
	if (env)
		return (ft_strdup_env(env->value));
	return (NULL);
}
