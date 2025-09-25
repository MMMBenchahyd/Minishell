/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:23 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/12 18:03:05 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_xpnd(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static size_t	in_qoute_len(const char *line)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '"';
	if (line[i++] == '\'')
		quote = '\'';
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	return (i);
}

static size_t	check_op_len(char **s)
{
	static int	p_typ;
	size_t		i;

	i = 0;
	if (!ft_strncmp(*s, "<<", 2) || !ft_strncmp(*s, ">>", 2))
	{
		if (!ft_strncmp(*s, "<<", 2))
			p_typ = 1;
		return (2);
	}
	else if (p_typ == 1 && **s == '$')
	{
		p_typ = 0;
		while ((*s)[i] && !ft_strchr((*s)[i], " 	\'\"<>|"))
			i++;
		return (i);
	}
	else if (!ft_strncmp(*s, "$?", 2)
		|| ((*s)[0] == '$' && ft_isdigit((*s)[1])))
		return (2);
	else if ((*s)[0] == '>' || (*s)[0] == '<' || (*s)[0] == '|' ||
				((*s)[0] == '$' && !(*s)[1]))
		return (1);
	return (0);
}

void	count_token_len(char **line, size_t i)
{
	size_t	len;

	len = check_op_len(line);
	if (len)
		*line += len;
	else if ((*line)[0] == '\'' || (*line)[0] == '"')
		*line += in_qoute_len(*line);
	else
	{
		if ((*line)[0] == '$')
			i++;
		if (check_valid_xpnd((*line)[i]))
		{
			while ((*line)[i] && (!ft_strchr((*line)[i], " 	\'\"<>|$")
				&& check_valid_xpnd((*line)[i])))
				i++;
		}
		else
		{
			while ((*line)[i] && !ft_strchr((*line)[i], " 	\'\"<>|$"))
				i++;
		}
		*line += i;
	}
}
