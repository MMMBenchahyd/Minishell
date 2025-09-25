/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:02:42 by mbenchah          #+#    #+#             */
/*   Updated: 2025/06/09 18:02:45 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_random_name(void)
{
	char		*num_str;
	char		*name;
	static int	counter;

	if (counter > 1018)
		counter = 0;
	num_str = ft_itoa(counter++ + 1000);
	name = ft_strjoin("/tmp/.heredoc_", num_str);
	return (name);
}

void	unlink_heredoc(char **heredoc, int num_heredocs)
{
	int	i;

	i = 0;
	while (i < num_heredocs && heredoc[i])
	{
		unlink(heredoc[i]);
		i++;
	}
}

static int	check_quotes(t_token *token)
{
	if (token->type == T_SINGLE_QUOTE || token->type == T_DOUBLE_QUOTE)
		return (1);
	return (0);
}

char	*read_from_hdoc(t_redirect *redirect, char *name)
{
	char	*line;
	int		fd;

	fd = ft_open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	ft_set_read_stat(2);
	while (1)
	{
		line = ft_readline("> ");
		if (!line || !ft_strcmp(line, redirect->file.value))
		{
			ft_set_read_stat(1);
			break ;
		}
		if (*ft_get_read_stat() == 3)
			return (close(fd), ft_set_read_stat(1), NULL);
		if (!check_quotes(&redirect->file))
			line = expand_in_qoute(line);
		ft_putendl_fd(line, fd);
	}
	close(fd);
	return (name);
}

int	process_cmd_heredocs(t_cmd *cmd, char **heredoc, int hdoc_count)
{
	t_redirect	**redirect;

	redirect = cmd->files;
	while (redirect && *redirect)
	{
		if ((*redirect)->type == T_DOUBLE_LESS)
		{
			heredoc[hdoc_count] = read_from_hdoc(*redirect, get_random_name());
			if (!heredoc[hdoc_count])
				return (-1);
			hdoc_count++;
		}
		redirect++;
	}
	return (hdoc_count);
}
