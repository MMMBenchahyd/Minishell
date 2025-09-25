/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:45 by aanbadi           #+#    #+#             */
/*   Updated: 2025/09/25 13:16:58 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	join_adjacent_tokens(t_token *curr, t_token *nxt_tkn)
{
	if (nxt_tkn->type == T_DOUBLE_QUOTE || nxt_tkn->type == T_SINGLE_QUOTE)
		curr->type = nxt_tkn->type;
	curr->value = ft_strjoin(curr->value, nxt_tkn->value);
	curr->next = nxt_tkn->next;
}

static t_token	*join_token(t_token *token)
{
	t_token	*curr;

	if (!token)
		return (NULL);
	curr = token;
	while (curr && curr->next)
	{
		if (!ft_strcmp(curr->next->value, "") && curr->next->type == T_EXPANDED)
		{
			if (!(!ft_strcmp(curr->value, " ") && curr->type == T_EXPANDED))
				if (!curr->next->a_sp)
					curr->next->value = ft_strdup(" ");
			curr = curr->next;
		}
		else if (!curr->next->a_sp && !check_operator(curr)
			&& !check_operator(curr->next))
			join_adjacent_tokens(curr, curr->next);
		else
			curr = curr->next;
	}
	return (token);
}

static int	skip_dollar_qoute(const char *start, char *value)
{
	if ((!ft_strncmp(start, "$\"", 2) || !ft_strncmp(start, "$\'", 2))
		&& ft_strlen(value) == 1)
		return (1);
	return (0);
}

static t_token	*input_to_token(char *input, t_token *token)
{
	const char		*start;
	char			*value;
	int				spc_n[2];

	if (!input)
		return (NULL);
	input += ft_strspn(input, " 	");
	ft_memset(spc_n, 0, sizeof(spc_n));
	while (*input)
	{
		start = input;
		count_token_len(&input, 0);
		value = ft_xtract(start, input);
		if (skip_dollar_qoute(start, value))
			continue ;
		if (ft_token_type(value) == T_PIPE)
			ft_set_status(0);
		spc_n[NEW]++;
		if (add_list(&token, check_home(value, ft_token_type(value)),
				ft_token_type(value), spc_n))
			return (ft_free(), ft_set_status(1), NULL);
		spc_n[AF_S] = ft_strchr(*input, " 	");
		input += ft_strspn(input, " 	");
	}
	return (join_token(token));
}

t_token	*lexer(void)
{
	t_token	*token;
	char	*input;

	ft_s_ret(0);
	input = ft_readline("minishell> ");
	if (input && ft_strcmp(input, ""))
		add_history(input);
	if (!check_valid_qoutes(input))
	{
		ft_set_status(2);
		return (ft_putstr_fd(SNTX_ERR, STDERR_FILENO), NULL);
	}
	if (!check_all_quotes(input))
		return (ft_putstr_fd(MSERR, STDERR_FILENO), ft_set_status(127), NULL);
	token = input_to_token(input, NULL);
	if (!token)
		return (NULL);
	if (check_valid_op(token))
	{
		ft_putstr_fd(SNTX_ERR, STDERR_FILENO);
		return (ft_set_status(2), ft_free(), NULL);
	}
	return (token);
}
