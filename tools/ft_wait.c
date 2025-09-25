/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:25 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:53:26 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait(pid_t lpid)
{
	pid_t	pid;
	int		status;

	if (lpid == EXIT_FAILURE)
	{
		ft_set_status(EXIT_FAILURE);
		return ;
	}
	while (1)
	{
		pid = wait(&status);
		if (pid < 0)
			break ;
		if (pid == lpid)
		{
			if (WIFEXITED(status))
				ft_set_status(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				ft_set_status(128 + WTERMSIG(status));
		}
	}
	ft_set_read_stat(1);
}
