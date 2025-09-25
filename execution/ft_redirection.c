/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:52:34 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 18:03:06 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_output_file(t_redirect *redir)
{
	int		flags;
	char	*name;

	name = redir->file.value;
	if (redir->type == T_DOUBLE_GREATER)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	return (ft_open(name, flags, 0644));
}

static int	open_input_file(t_redirect *redir, char **heredoc, int *hdoc_indx)
{
	char	*name;

	if (redir->type == T_DOUBLE_LESS)
		name = heredoc[(*hdoc_indx)++];
	else
		name = redir->file.value;
	return (ft_open(name, O_RDONLY, -1));
}

static void	safe_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

static int	setup_redirection(t_redirect *redir, int *io_fd,
						char **heredoc, int *hdoc_indx)
{
	if (redir->type == T_DOUBLE_GREATER || redir->type == T_GREATER)
	{
		safe_close(&io_fd[1]);
		io_fd[1] = open_output_file(redir);
	}
	else
	{
		safe_close(&io_fd[0]);
		io_fd[0] = open_input_file(redir, heredoc, hdoc_indx);
	}
	if (io_fd[0] == -1 || io_fd[1] == -1)
		return (-1);
	return (0);
}

int	ft_redirection(t_cmd *cmd, char **heredoc, int hdoc_indx)
{
	int	i;
	int	io_fd[2];

	if (!cmd->files || !cmd->files[0])
		return (0);
	i = -1;
	io_fd[0] = -100;
	io_fd[1] = -100;
	while (cmd->files[++i] && io_fd[0] != -1 && io_fd[1] != -1)
	{
		if (setup_redirection(cmd->files[i], io_fd,
				heredoc, &hdoc_indx) == -1)
			break ;
	}
	if (io_fd[0] == -1 || io_fd[1] == -1)
		return (-1);
	if (io_fd[0] != -100 && ft_dup2(io_fd[0], STDIN_FILENO) != -1)
		close(io_fd[0]);
	if (io_fd[1] != -100 && ft_dup2(io_fd[1], STDOUT_FILENO) != -1)
		close(io_fd[1]);
	return (0);
}
