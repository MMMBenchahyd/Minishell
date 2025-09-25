/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:52:43 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/12 18:04:28 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator(t_token *token)
{
	if (check_redirect(token->type) || token->type == T_PIPE)
		return (1);
	return (0);
}

int	check_redirect(int type)
{
	if (type == T_DOUBLE_LESS || type == T_DOUBLE_GREATER)
		return (1);
	if (type == T_LESS || type == T_GREATER)
		return (1);
	return (0);
}
