/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:52:10 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:52:11 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*ft_get_status(void)
{
	static int	status;

	return (&status);
}

void	ft_set_status(int status)
{
	int	*ptr;

	ptr = ft_get_status();
	*ptr = status;
}
