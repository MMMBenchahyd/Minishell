/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:07 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:53:08 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_gc	**ft_cmd_gc(char i)
{
	static t_gc	*head;

	if (!i)
		head = NULL;
	return (&head);
}

void	*ft_malloc(size_t size)
{
	t_gc	**head;
	t_gc	*new;
	void	*p;

	head = ft_cmd_gc(1);
	p = malloc(size);
	if (!p)
	{
		ft_putendl_fd("minishell: malloc failed", STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
	new = malloc(sizeof(t_gc));
	if (!new)
	{
		free(p);
		ft_putendl_fd("minishell: malloc failed", STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
	new->next = *head;
	new->ptr = p;
	*head = new;
	return (p);
}

void	ft_free(void)
{
	t_gc	*ptr;
	t_gc	*curr;

	curr = *ft_cmd_gc(1);
	while (curr)
	{
		ptr = curr;
		curr = curr->next;
		free(ptr->ptr);
		free(ptr);
	}
	ft_cmd_gc(0);
}
