/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:04 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 19:02:26 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_env_error(char *str)
{
	ft_putstr_fd("env: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\': No such file or directory\n", STDERR_FILENO);
}

static void	print_env_var(t_env *var)
{
	if (var->key && var->equal && ft_strcmp(var->equal, ""))
	{
		ft_putstr_fd(var->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(var->value, STDOUT_FILENO);
	}
}

int	env_builtin(t_cmd cmd)
{
	t_env	**env;
	t_env	*current;
	int		j;

	j = 0;
	env = ft_env_head();
	current = *env;
	if (!current)
		return (EXIT_FAILURE);
	if (count_args(cmd, &j) > 0)
	{
		print_env_error(cmd.tokens[j]->value);
		return (127);
	}
	while (current)
	{
		print_env_var(current);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
