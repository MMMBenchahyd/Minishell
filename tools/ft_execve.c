/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:52:57 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 00:58:46 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_arg_count(t_cmd cmd)
{
	int	cnt;
	int	i;

	if (!cmd.tokens)
		return (0);
	cnt = 0;
	i = 0;
	while (cmd.tokens[i])
	{
		if (!cmd.tokens[i]->value)
			break ;
		if (cmd.tokens[i]->type == T_EXPANDED)
			cnt += count_word(cmd.tokens[i]->value, ' ');
		else
			cnt++;
		i++;
	}
	return (cnt);
}

char	**ft_arg_arr(t_cmd cmd)
{
	int		i;
	char	**arg;
	char	**splt;
	char	**or_arg;

	arg = ft_malloc(sizeof(char *) * (ft_arg_count(cmd) + 1));
	i = -1;
	or_arg = arg;
	while (cmd.tokens[++i])
	{
		if (!cmd.tokens[i]->value)
			break ;
		if (cmd.tokens[i]->type == T_EXPANDED)
		{
			splt = ft_split(cmd.tokens[i]->value, ' ');
			while (splt && *splt)
				*arg++ = *splt++;
		}
		else
			*arg++ = cmd.tokens[i]->value;
	}
	*arg = NULL;
	return (or_arg);
}

void	ft_execve(t_cmd cmd)
{
	char	**arg;
	char	*path;

	arg = ft_arg_arr(cmd);
	if (!arg || !arg[0])
		ft_exit(*ft_get_status());
	path = get_cmd_path(arg[0]);
	if (!path)
		ft_exit(*ft_get_status());
	execve(path, arg, ft_lstenv_arr(path));
	perror("minishell");
	ft_exit(0);
}
