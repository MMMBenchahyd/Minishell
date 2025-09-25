/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstenv_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:02:51 by mbenchah          #+#    #+#             */
/*   Updated: 2025/06/09 18:02:53 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_lstenv_arr(char *cmd)
{
	char	**env;
	t_env	*head;
	int		i;

	head = *ft_env_head();
	env = ft_malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	i = 0;
	while (head)
	{
		if (!ft_strcmp(head->key, "_"))
			ft_update_env(head->key, cmd);
		if (!ft_strcmp(head->key, "SHLVL"))
			head->value = ft_strdup_env(ft_itoa(ft_atoi(head->value) + 1));
		if (head->value)
			env[i++] = ft_strjoin(head->key, ft_strjoin("=", head->value));
		head = head->next;
	}
	env[i] = NULL;
	return (env);
}
