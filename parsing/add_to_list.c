/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:11 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:55:11 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_dlr_err(char *value)
{
	char	*str;

	if (!value)
		str = "minishell: syntax error near unexpected token `newline'\n";
	else
	{
		str = ft_strjoin("minishell: ", value);
		str = ft_strjoin(str, ": ambiguous redirect\n");
	}
	ft_putstr_fd(str, STDERR_FILENO);
}

static int	should_expand(int type, int p_typ)
{
	return ((type == T_DOLLAR_EXPAND || type == T_IGN || type == T_EXIT_STATUS)
		&& p_typ != T_DOUBLE_LESS);
}

static int	is_cmd(int p_typ, int *spc_n, int *ret, char *value)
{
	static int	equal;

	if (spc_n[AF_S] || spc_n[NEW])
		equal = 0;
	if (*value == '=' || !ft_strcmp(value, "+="))
		equal = 1;
	if ((*ret && !spc_n[AF_S]) || (p_typ == T_LESS
			|| p_typ == T_GREATER || p_typ == T_DOUBLE_GREATER))
		*ret = 1;
	else
		*ret = 0;
	return (equal);
}

int	add_list(t_token **token, char *value, int type, int *spc_n)
{
	static int	a_s;
	static int	p_typ = T_CMND;
	static int	cmd_ret[2];

	cmd_ret[CMD] = is_cmd(p_typ, spc_n, &cmd_ret[RET], value);
	if (a_s == 1)
		spc_n[AF_S] = a_s--;
	if (type == T_DOUBLE_QUOTE && !all_dollar(value) && p_typ != T_DOUBLE_LESS)
		value = expand_in_qoute(value);
	if (should_expand(type, p_typ))
	{
		if (p_typ == T_LESS || p_typ == T_GREATER || p_typ == T_DOUBLE_GREATER)
			cmd_ret[RET] = 1;
		a_s = expand_token(token, value, spc_n[AF_S], cmd_ret);
		if (a_s == -1)
			return (print_dlr_err(value), -1);
	}
	else if (p_typ == 5 && type == T_CMND && ft_strcmp(value, "-") == 0)
		return (ft_set_status(2), print_dlr_err(0), -1);
	else
		ft_lstadd_back_token(token, ft_lstnew_token(value, type, spc_n[AF_S]));
	if (token && *token)
		p_typ = type;
	return (0);
}
