/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:51:35 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:51:36 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back_env(t_env *new)
{
	t_env	*ptr;
	t_env	**head;

	head = ft_env_head();
	if (head)
	{
		ptr = ft_lstlast(*head);
		if (ptr)
			ptr->next = new;
		else
			*head = new;
	}
}

t_env	*ft_lstnew_env(char *key, char *equal, char *value)
{
	t_env	*new;

	new = ft_malloc_env(sizeof(t_env));
	new->next = NULL;
	new->key = key;
	new->equal = equal;
	new->value = value;
	return (new);
}

int	ft_lstsize(t_env *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst ->next;
	}
	return (len);
}
