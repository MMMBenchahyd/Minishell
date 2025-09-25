/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:55:49 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/15 19:38:56 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_redirect	*create_redirect(t_token *token, t_token *next_token)
{
	t_redirect	*redir;

	redir = ft_malloc(sizeof(t_redirect));
	redir->file.value = next_token->value;
	redir->file.type = next_token->type;
	redir->type = token->type;
	return (redir);
}

static t_token	*process_redirection(t_cmd *cmd, t_token *token, int *index,
												int *hdoc_count)
{
	if (token->type == T_DOUBLE_LESS)
		(*hdoc_count)++;
	cmd->files[*index] = create_redirect(token, token->next);
	(*index)++;
	return (token->next);
}

static t_token	*parse_cmd_tokens(t_cmd *cmd, t_token *token, int *hdoc_count)
{
	int	token_idx;
	int	file_idx;

	token_idx = 0;
	file_idx = 0;
	cmd->hdoc_indx = *hdoc_count;
	cmd->last = 0;
	while (token && token->type != T_PIPE)
	{
		if (check_redirect(token->type))
			token = process_redirection(cmd, token, &file_idx, hdoc_count);
		else
		{
			cmd->tokens[token_idx++] = token;
		}
		token = token->next;
	}
	cmd->tokens[token_idx] = NULL;
	cmd->files[file_idx] = NULL;
	return (token);
}

static void	init_cmds(t_token *token, t_cmd *cmd)
{
	cmd->files = ft_malloc((count_files(token) + 1) * sizeof(t_redirect *));
	cmd->tokens = ft_malloc((count_tokens(token) + 1) * sizeof(t_token *));
}

t_cmd	*parsering(t_token *token)
{
	int		hdoc_count;
	int		cmd_count;
	int		i;
	t_cmd	*cmds;

	i = -1;
	hdoc_count = 0;
	cmd_count = count_cmds(token);
	if (cmd_count > 3330)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		ft_set_status(2);
		return (0);
	}
	cmds = ft_malloc(cmd_count * sizeof(t_cmd));
	while (++i < cmd_count)
	{
		init_cmds(token, &cmds[i]);
		token = parse_cmd_tokens(&cmds[i], token, &hdoc_count);
		if (token)
			token = token->next;
	}
	cmds[cmd_count - 1].last = 1;
	return (cmds);
}
