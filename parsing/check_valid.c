/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:15 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 17:47:53 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_s_ret(int in)
{
	static int	s_ret;

	if (in != -1)
		s_ret = in;
	return (s_ret);
}

int	check_valid_qoutes(const char *input)
{
	int	in_squote;
	int	in_dquote;
	int	i;

	if (!input)
		return (1);
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		i++;
	}
	if (!in_squote && !in_dquote)
		return (1);
	return (0);
}

int	check_valid_op(t_token *token)
{
	int	is_first_token;
	int	is_pipe_before_redir;

	is_first_token = 1;
	while (token)
	{
		if (token->type == T_PIPE && is_first_token)
			return (1);
		if (check_operator(token))
		{
			if (!token->next)
				return (1);
			is_pipe_before_redir = (token->type == T_PIPE
					&& check_redirect(token->next->type));
			if (check_operator(token->next) && !is_pipe_before_redir)
				return (1);
		}
		token = token->next;
		is_first_token = 0;
	}
	return (0);
}
