/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:13 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/10 16:09:22 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_piped_input(void)
{
	int		fd;
	char	*input;

	fd = ft_dup(STDOUT_FILENO);
	if (fd == -1)
		ft_exit(EXIT_FAILURE);
	close(STDOUT_FILENO);
	input = readline(0);
	if (ft_dup2(fd, STDOUT_FILENO) == -1)
		ft_exit(EXIT_FAILURE);
	close(fd);
	return (input);
}

char	*ft_readline(const char *prompt)
{
	char	*line;
	char	*tmp;

	if (isatty(STDIN_FILENO))
		tmp = readline(prompt);
	else
		tmp = ft_piped_input();
	if (!tmp && *ft_get_read_stat() == 1)
	{
		if (isatty(STDIN_FILENO))
			ft_putendl_fd("exit", STDOUT_FILENO);
		ft_exit(*ft_get_status());
	}
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}
