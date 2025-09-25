/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:34 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:48:35 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_env_node(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_builtin(t_cmd cmd)
{
	int		i;
	t_env	**head;

	head = ft_env_head();
	if (*head == NULL)
		return (EXIT_FAILURE);
	i = 1;
	while (cmd.tokens[i] && cmd.tokens[i]->value)
	{
		remove_env_node(head, cmd.tokens[i]->value);
		i++;
	}
	return (EXIT_SUCCESS);
}
