/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:52 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/13 18:18:55 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	ft_set_read_stat(1);
	set_signals();
	set_env(env);
	tcgetattr(STDIN_FILENO, ft_get_termios());
	while (1)
	{
		tokens = lexer();
		if (tokens)
		{
			cmds = parsering(tokens);
			ft_exec(cmds, count_cmds(tokens), count_hdoc(tokens));
			tcsetattr(STDIN_FILENO, TCSANOW, ft_get_termios());
			ft_free();
			close_all_fds();
		}
	}
	free_env();
	return (EXIT_SUCCESS);
}
