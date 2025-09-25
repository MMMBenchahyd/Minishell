/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:11 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/10 17:30:29 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	perr_exprt(char *arg)
{
	char	*str;

	str = ft_strjoin("minishell: export: `", arg);
	str = ft_strjoin(str, "\': not a valid identifier\n");
	ft_putstr_fd(str, STDERR_FILENO);
}

int	handle_export_argument(char *arg)
{
	t_env	*node;

	node = ft_envstr_to_lst(arg);
	if (node && !check_valid_env_key(node->key))
	{
		perr_exprt(arg);
		ft_set_status(EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	export_handle_argument(node);
	return (EXIT_SUCCESS);
}

static void	print_env_var(t_env *env)
{
	if (!env->key || !ft_strcmp(env->key, "_"))
		return ;
	printf("declare -x %s", env->key);
	if (env->equal && (!ft_strcmp(env->equal, "+=")
			|| *env->equal == '=') && env->value)
		printf("=\"%s\"", env->value);
	printf("\n");
}

int	export_print(void)
{
	t_env	*env;
	t_env	*current;

	env = ft_sort_env(ft_lstenv_dup());
	current = env;
	while (current)
	{
		print_env_var(current);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

void	export_handle_argument(t_env *node)
{
	if (!node->key || !ft_strcmp(node->key, "_"))
		return ;
	if (ft_envchr(node->key))
	{
		if (node->equal && !ft_strcmp(node->equal, "="))
			ft_update_env(node->key, node->value);
		else if (node->equal && !ft_strcmp(node->equal, "+="))
			ft_append_env(node->key, node->value);
	}
	else
		ft_lstadd_back_env(node);
}
