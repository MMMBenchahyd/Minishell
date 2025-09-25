/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:34 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 19:05:43 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_cmd cmd, int *j)
{
	int	i;
	int	cnt;

	cnt = 0;
	if (!cmd.tokens || !cmd.tokens[0])
		return (0);
	i = 1;
	while (cmd.tokens[i])
	{
		if (!(!ft_strcmp(cmd.tokens[i]->value, "")
				&& cmd.tokens[i]->type == T_EXPANDED))
		{
			if (*j == 0)
				*j = i;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static t_token	*ft_lstlast_token(t_token *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (lst)
	{
		ptr = ft_lstlast_token(*lst);
		if (ptr)
			ptr->next = new;
		else
			*lst = new;
	}
}

t_token	*ft_lstnew_token(char *value, int type, int after_space)
{
	t_token	*token;
	char	*end;

	token = ft_malloc(sizeof(t_token));
	if (type == T_SINGLE_QUOTE || type == T_DOUBLE_QUOTE)
	{
		end = value + ft_strlen(value) - 1;
		value = ft_xtract(value + 1, end);
	}
	token->value = value;
	token->a_sp = after_space;
	token->type = type;
	token->next = NULL;
	return (token);
}
