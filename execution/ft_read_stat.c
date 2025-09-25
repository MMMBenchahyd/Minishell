/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:02:59 by mbenchah          #+#    #+#             */
/*   Updated: 2025/06/09 18:02:59 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*ft_get_read_stat(void)
{
	static int	stat;

	return (&stat);
}

void	ft_set_read_stat(int stat)
{
	int	*tmp;

	tmp = ft_get_read_stat();
	*tmp = stat;
	return ;
}
