/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:38 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:55:39 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_token_type_2(const char *value)
{
	if (!ft_strncmp(value, "<<", 2))
		return (T_DOUBLE_LESS);
	else if (!ft_strncmp(value, ">>", 2))
		return (T_DOUBLE_GREATER);
	return ((*value == '\'') * (T_SINGLE_QUOTE) | \
		(*value == '"') * (T_DOUBLE_QUOTE));
}

int	ft_token_type(const char *value)
{
	int	ret;

	ret = 0;
	if (!*(value + 1))
	{
		ret = ((*value == '|') * T_PIPE + (*value == '<') * T_LESS \
			+ (*value == '>') * T_GREATER \
			+ (*value == '$') * T_SINGLE_DOLLAR);
	}
	else if (*value == '$')
	{
		ret = (ft_isdigit(value[1]) * (T_IGN) | \
			((!ft_strncmp(value, "$?", 2)) * T_EXIT_STATUS));
		ret += (!ret) * T_DOLLAR_EXPAND;
	}
	else
		ret = ft_token_type_2(value);
	return (ret);
}
