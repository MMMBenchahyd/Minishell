/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:00 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:48:01 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flag(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !ft_strcmp(str, ""))
		return (0);
	if (str[0] != '-')
		return (0);
	if (str[0] == '-' && str[1])
		str++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static char	*ft_splt_if(t_cmd cmd, char *str, int first_print, int i)
{
	if (!ft_strcmp(cmd.tokens[i]->value, " ")
		&& cmd.tokens[i]->type == T_EXPANDED)
	{
		if (cmd.tokens[i]->next)
		{
			cmd.tokens[i]->next->a_sp = 1;
			return (str);
		}
		else
			return (str);
	}
	if (first_print && cmd.tokens[i]->a_sp
		&& !(!ft_strcmp(cmd.tokens[i]->value, "")
			&& cmd.tokens[i]->type == T_EXPANDED))
		str = ft_strjoin(str, " ");
	str = ft_strjoin(str, cmd.tokens[i]->value);
	return (str);
}

int	echo_builtin(t_cmd cmd)
{
	int		i;
	int		flag_n;
	int		first_print;
	char	*str;

	i = 1;
	flag_n = 0;
	first_print = 0;
	str = 0;
	while (cmd.tokens[i] && cmd.tokens[i]->value
		&& check_flag(cmd.tokens[i]->value))
		flag_n = i++;
	while (cmd.tokens[i] && cmd.tokens[i]->value)
	{
		str = ft_splt_if(cmd, str, first_print++, i);
		i++;
	}
	if (!flag_n)
		str = ft_strjoin(str, "\n");
	ft_putstr_fd(str, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
