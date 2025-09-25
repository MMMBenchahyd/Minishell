/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:27 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 17:38:44 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_expandlen(char *input, int len)
{
	char	*start;

	while (input && *input)
	{
		if (*input++ == '$' && *(input) && !ft_strchr(*(input), " 	\'\"<>|"))
		{
			if (ft_isdigit(*input))
				input++;
			else if (*input == '?')
			{
				input++;
				len += ft_strlen(ft_itoa(*ft_get_status()));
			}
			else
			{
				start = input;
				while (check_valid_xpnd(*input))
					input++;
				len += ft_strlen(ft_getenv(ft_xtract(start, input)));
			}
		}
		else
			len++;
	}
	return (len);
}

static size_t	ft_expand_var(char *start, char **input, char *ptr)
{
	char	*xpnd;

	xpnd = NULL;
	if (**input <= '9' && **input >= '0')
		(*input)++;
	else if (**input == '?')
	{
		xpnd = ft_itoa(*ft_get_status());
		(*input)++;
	}
	else
	{
		while (check_valid_xpnd(**input))
			(*input)++;
		xpnd = ft_xtract(start, *input);
		xpnd = ft_getenv(xpnd);
	}
	ft_memcpy(ptr, xpnd, ft_strlen(xpnd));
	return (ft_strlen(xpnd));
}

char	*expand_in_qoute(char *input)
{
	char	*ptr;
	int		i;

	if (!input)
		return (NULL);
	if (all_dollar(input))
		return (input);
	i = 0;
	ptr = ft_malloc(ft_expandlen(input, 0) + 1);
	while (*input)
	{
		if (*input == '$' && *(input + 1)
			&& !ft_strchr(*(input + 1), " 	\'\"<>|"))
		{
			input++;
			i += ft_expand_var(input, &input, &ptr[i]);
		}
		else
			ptr[i++] = *input++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	*xpn(char *str, char **xpnd)
{
	if (!ft_strncmp(str, "$?", 2))
		*xpnd = ft_itoa(*ft_get_status());
	else
	{
		*xpnd = ft_getenv(str + 1);
		if (!*xpnd)
			*xpnd = ft_strdup(" ");
	}	
	return (*xpnd);
}

int	expand_token(t_token **token, char *str, int a_s, int *cmd_ret)
{
	char		*xpnd;
	char		*start;
	char		*value;

	if (!ft_s_ret(-1))
		ft_s_ret(cmd_ret[RET]);
	if (!xpn(str, &xpnd) || !ft_strcmp(xpnd, ""))
		return (a_s);
	if (ft_s_ret(-1) == 1 && (check_ambg(str, " 	") || ft_isallspace(xpnd)))
		return (-1);
	while (xpnd && *xpnd && !cmd_ret[CMD])
	{
		xpnd += ft_strspn(xpnd, " 	");
		start = xpnd;
		count_token_len(&xpnd, 0);
		value = ft_xtract(start, xpnd);
		ft_lstadd_back_token(token, ft_lstnew_token(value, T_EXPANDED, a_s));
		a_s = ft_strchr(*xpnd, " 	");
		xpnd += ft_strspn(xpnd, " 	");
	}
	if (cmd_ret[CMD])
		ft_lstadd_back_token(token, ft_lstnew_token(xpnd, T_EXPANDED, a_s));
	return (0);
}
