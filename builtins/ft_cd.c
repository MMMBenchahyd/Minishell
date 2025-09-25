/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:47:56 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 19:42:28 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_cd_err(char *str)
{
	char	*err_msg;

	if (!str)
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	else
	{
		err_msg = ft_strjoin(ft_strjoin("minishell: cd: ", str), " not set\n");
		ft_putstr_fd(err_msg, STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}

static int	cd_is_special_case(t_cmd cmd, int j)
{
	char	*pth;

	pth = cmd.tokens[j]->value;
	if (!ft_strcmp(pth, "--") || !ft_strcmp(pth, "-"))
		return (1);
	return (0);
}

static int	cd_handle_special_path(char *env_var, char *suffix)
{
	char	*env_value;
	char	*full_path;

	env_value = ft_getenv(env_var);
	if (!env_value)
		return (print_cd_err(env_var));
	if (suffix)
		full_path = ft_strjoin(env_value, suffix);
	else
		full_path = ft_strdup(env_value);
	return (ft_chdir(full_path));
}

static int	handle_empty(t_cmd cmd, int j)
{
	if ((!ft_strcmp(cmd.tokens[j]->value, "")
			&& cmd.tokens[j]->type != T_EXPANDED))
		return (0);
	else if (!ft_strcmp(cmd.tokens[j]->value, " ")
		&& cmd.tokens[j]->type == T_EXPANDED)
		return (1);
	return (2);
}

int	cd_builtin(t_cmd cmd)
{
	int	j;

	j = 0;
	if (count_args(cmd, &j) > 1)
		return (print_cd_err(0));
	if (count_args(cmd, &j) == 0)
		return (cd_handle_special_path("HOME", NULL));
	if (!handle_empty(cmd, j))
		return (0);
	else if (handle_empty(cmd, j) == 1)
		return (cd_handle_special_path("HOME", NULL));
	if (cd_is_special_case(cmd, j) == 1)
	{
		if (!ft_strcmp(cmd.tokens[j]->value, "-"))
			return (cd_handle_special_path("OLDPWD", NULL));
		else
			return (cd_handle_special_path("HOME", NULL));
	}
	return (ft_chdir(cmd.tokens[j]->value));
}
