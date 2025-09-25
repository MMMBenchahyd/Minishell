/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:08 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 19:28:13 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	perr_exit(char *arg)
{
	char	*err_msg;

	if (arg)
	{
		err_msg = ft_strjoin("minishell: exit: ", arg);
		err_msg = ft_strjoin(err_msg, ": numeric argument required\n");
		ft_putstr_fd(err_msg, STDERR_FILENO);
	}
	else
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	return (1);
}

static unsigned long long	ft_atol(const char *str)
{
	unsigned long long	num;

	num = 0;
	while (ft_isspace(*str))
		str++;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (num * 10 + (*str - '0') > LONG_MAX)
			return (1);
		num = num * 10 + (*str - '0');
		str++;
	}
	return (0);
}

static int	exit_is_valid_status(char *str)
{
	int		i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	if (ft_atol(str))
		return (0);
	return (1);
}

void	exit_builtin(t_cmd cmd, int ext)
{
	char	*arg;
	int		arg_count;
	int		j;

	j = 0;
	arg_count = count_args(cmd, &j);
	if (ext)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (arg_count == 0)
		ft_exit(*ft_get_status());
	arg = cmd.tokens[j]->value;
	if (!exit_is_valid_status(arg) && perr_exit(arg))
		ft_exit(2);
	if (arg_count > 1)
	{
		perr_exit(0);
		if (ext)
			ft_set_status(1);
		else
			ft_exit(1);
		return ;
	}
	ft_exit(ft_atoi(arg));
}
