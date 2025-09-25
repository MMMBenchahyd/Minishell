/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:51:31 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:51:32 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gc	**ft_env_gc(void)
{
	static t_gc	*head;

	return (&head);
}

void	*ft_malloc_env(size_t size)
{
	t_gc	**head;
	t_gc	*new;
	void	*p;

	head = ft_env_gc();
	p = malloc(size);
	if (!p)
	{
		ft_putendl_fd("minishell: env malloc failed", STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
	new = malloc(sizeof(t_gc));
	if (!new)
	{
		free(p);
		ft_putendl_fd("minishell: env malloc failed", STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
	new->ptr = p;
	new->next = *head;
	*head = new;
	return (p);
}

void	free_env(void)
{
	t_gc	*head;
	t_gc	*ptr;

	head = *ft_env_gc();
	while (head)
	{
		ptr = head;
		head = head->next;
		free(ptr->ptr);
		free(ptr);
	}
}
