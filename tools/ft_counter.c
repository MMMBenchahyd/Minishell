/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_counter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:52:54 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/12 17:58:39 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == T_PIPE)
			i++;
		if (token->next == NULL)
			return (i + 1);
		token = token->next;
	}
	return (1);
}

int	count_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != T_PIPE)
	{
		i++;
		if (check_redirect(token->type))
		{
			token = token->next;
			i--;
		}
		token = token->next;
	}
	return (i);
}

int	count_files(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == T_GREATER || token->type == T_DOUBLE_GREATER
			|| token->type == T_LESS || token->type == T_DOUBLE_LESS)
			i++;
		token = token->next;
	}
	return (i);
}

int	count_hdoc(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == T_DOUBLE_LESS)
			i++;
		if (token->next == NULL)
			return (i);
		token = token->next;
	}
	return (0);
}
