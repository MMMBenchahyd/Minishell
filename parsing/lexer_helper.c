/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:42 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:55:42 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_home(char *value, int token_type)
{
	char	*home_path;

	if (value && (!ft_strncmp(value, "~/", 2) || !ft_strcmp(value, "~")))
	{
		if (token_type != T_DOUBLE_QUOTE && token_type != T_SINGLE_QUOTE)
		{
			home_path = ft_getenv("HOME");
			if (home_path)
			{
				value = ft_strjoin(home_path, value + 1);
			}
		}
	}
	return (value);
}

int	all_dollar(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '$' && str[i] != '\'' && str[i] != '"')
			return (0);
		i++;
	}
	return (1);
}

int	check_all_quotes(char *input)
{
	size_t	i;

	i = 0;
	if (!input || !input[0])
		return (1);
	while (input[i])
	{
		if (!(input[i] == '\'' || input[i] == '"'))
			break ;
		i++;
	}
	if (ft_strlen(input) == i)
		return (0);
	return (1);
}
