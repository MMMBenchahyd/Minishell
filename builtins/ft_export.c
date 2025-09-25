/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:15 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 19:43:03 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_addback_lst_dup(t_env **lst, t_env *new)
{
	t_env	*current;

	current = *lst;
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_env	*ft_lstenv_dup(void)
{
	t_env	**env;
	t_env	*env_copy;
	t_env	*current;
	t_env	*new;

	env = ft_env_head();
	if (!env)
		return (NULL);
	env_copy = NULL;
	current = *env;
	while (current)
	{
		new = ft_lstnew_env(current->key, current->equal, current->value);
		ft_addback_lst_dup(&env_copy, new);
		current = current->next;
	}
	return (env_copy);
}

static void	ft_swap_lst(t_env *node, t_env *next)
{
	char	*tmp_key;
	char	*tmp_value;
	char	*tmp_equal;

	tmp_key = node->key;
	tmp_value = node->value;
	tmp_equal = node->equal;
	node->key = next->key;
	node->value = next->value;
	node->equal = next->equal;
	next->key = tmp_key;
	next->value = tmp_value;
	next->equal = tmp_equal;
}

t_env	*ft_sort_env(t_env *env)
{
	int		swapped;
	t_env	*last;
	t_env	*current;

	last = NULL;
	if (!env)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = env;
		while (current->next != last)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				ft_swap_lst(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
	return (env);
}

int	export_builtin(t_cmd cmd)
{
	int	arg_count;
	int	i;

	i = 0;
	arg_count = count_args(cmd, &i);
	i = 1;
	if (arg_count == 0)
		return (export_print());
	while (cmd.tokens[i] && cmd.tokens[i]->value)
	{
		if ((!ft_strcmp(cmd.tokens[i]->value, "")
				&& cmd.tokens[i]->type == T_EXPANDED))
		{
			i++;
			continue ;
		}
		if (handle_export_argument(cmd.tokens[i]->value) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
