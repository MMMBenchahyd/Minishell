/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:52:05 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/13 01:55:39 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	env_is_empty(void)
{
	char	pwd[PATH_MAX];
	t_env	*node;

	node = ft_envstr_to_lst("PATH=/bin:/usr/bin");
	ft_lstadd_back_env(node);
	getcwd(pwd, PATH_MAX);
	node = ft_envstr_to_lst(ft_strjoin("PWD=", pwd));
	ft_hpwd(pwd, 0);
	ft_lstadd_back_env(node);
	node = ft_envstr_to_lst("SHLVL=1");
	ft_lstadd_back_env(node);
	node = ft_envstr_to_lst("_=env");
	ft_lstadd_back_env(node);
}

void	set_env(char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	if (!env || !env[0])
	{
		env_is_empty();
		return ;
	}
	while (env[i])
	{
		node = ft_envstr_to_lst(env[i]);
		if (!ft_strcmp(node->key, "_"))
			node->value = ft_strdup_env("env");
		ft_lstadd_back_env(node);
		i++;
	}
	ft_hpwd(ft_getenv("PWD"), 0);
}
