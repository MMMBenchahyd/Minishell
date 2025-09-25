/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:40 by mbenchah          #+#    #+#             */
/*   Updated: 2025/06/09 18:03:41 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_builtin_name(const char *name)
{
	int					i;
	static const char	*builtins[8] = {
		"cd", "echo", "env", "exit",
		"export", "pwd", "unset", NULL
	};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(name, builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(t_cmd cmd)
{
	if (!cmd.tokens || !cmd.tokens[0] || !cmd.tokens[0]->value)
		return (0);
	return (is_builtin_name(cmd.tokens[0]->value));
}

int	exec_builtin(t_cmd cmd)
{
	int			i;
	t_builtin	builtins[7];

	if (!cmd.tokens || !cmd.tokens[0])
		return (EXIT_FAILURE);
	builtins[0] = (t_builtin){"cd", cd_builtin};
	builtins[1] = (t_builtin){"echo", echo_builtin};
	builtins[2] = (t_builtin){"env", env_builtin};
	builtins[3] = (t_builtin){"export", export_builtin};
	builtins[4] = (t_builtin){"pwd", pwd_builtin};
	builtins[5] = (t_builtin){"unset", unset_builtin};
	builtins[6] = (t_builtin){NULL, NULL};
	i = 0;
	while (builtins[i].name != NULL)
	{
		if (!ft_strcmp(cmd.tokens[0]->value, builtins[i].name))
			return (builtins[i].func(cmd));
		i++;
	}
	return (EXIT_FAILURE);
}
