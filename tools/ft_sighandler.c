/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:21 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:53:22 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (*ft_get_read_stat() == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_set_status(130);
	}
	else if (*ft_get_read_stat() == 2)
	{
		ft_set_read_stat(3);
		ft_set_status(130);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			perror("ioctl");
	}
	close_all_fds();
}
