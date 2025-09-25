/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:02:36 by mbenchah          #+#    #+#             */
/*   Updated: 2025/06/15 19:21:53 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_mallo_heredoc(int hdoc_count)
{
	if (hdoc_count > 16)
	{
		ft_putendl_fd("minishell: maximum here-document count exceeded",
			STDERR_FILENO);
		ft_exit(2);
	}
	return (ft_malloc((hdoc_count + 1) * sizeof(char *)));
}

static void	ft_only_builtin(t_cmd cmd, char **heredoc)
{
	int	tmp_stdin;
	int	tmp_stdout;

	tmp_stdin = ft_dup(STDIN_FILENO);
	tmp_stdout = ft_dup(STDOUT_FILENO);
	if (tmp_stdin == -1 || tmp_stdout == -1)
		return ;
	if (ft_redirection(&cmd, heredoc, 0))
		ft_set_status(EXIT_FAILURE);
	else if (!ft_strcmp("exit", cmd.tokens[0]->value))
		exit_builtin(cmd, 1);
	else
		ft_set_status(exec_builtin(cmd));
	if (ft_dup2(tmp_stdin, STDIN_FILENO) == -1
		|| ft_dup2(tmp_stdout, STDOUT_FILENO) == -1)
		ft_exit(EXIT_FAILURE);
	close(tmp_stdin);
	close(tmp_stdout);
}

int	exec_multiple_cmds(t_cmd *cmds, int n_cmds, char **heredoc, int *last_pid)
{
	int		fd_in;
	int		i;

	i = -1;
	fd_in = STDIN_FILENO;
	while (++i < n_cmds && cmds[i].tokens)
	{
		fd_in = exec_bin(cmds[i], fd_in, heredoc, last_pid);
		if (fd_in == EXIT_FAILURE)
		{
			ft_wait(*last_pid);
			ft_set_status(EXIT_FAILURE);
			ft_exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int	ft_heredoc(t_cmd *cmds, int n_cmds, char **heredoc)
{
	int	cmd_idx;
	int	hdoc_count;

	cmd_idx = 0;
	hdoc_count = 0;
	if (!cmds || !heredoc)
		return (0);
	while (cmd_idx < n_cmds)
	{
		hdoc_count = process_cmd_heredocs(&cmds[cmd_idx], heredoc, hdoc_count);
		if (hdoc_count == -1)
		{
			unlink_heredoc(heredoc, hdoc_count);
			return (1);
		}
		cmd_idx++;
	}
	return (0);
}

int	ft_exec(t_cmd *cmds, int n_cmds, int hdoc_count)
{
	pid_t	last_pid;
	char	**heredoc;

	if (!cmds)
		return (0);
	last_pid = -1;
	heredoc = ft_mallo_heredoc(hdoc_count);
	if (ft_heredoc(cmds, n_cmds, heredoc))
		return (1);
	if (*ft_get_read_stat() == 3)
		return (ft_set_read_stat(1), 0);
	if (n_cmds == 1 && is_builtin(cmds[0]))
		ft_only_builtin(cmds[0], heredoc);
	else
	{
		if (exec_multiple_cmds(cmds, n_cmds, heredoc, &last_pid))
			return (unlink_heredoc(heredoc, hdoc_count), 1);
		ft_wait(last_pid);
	}
	unlink_heredoc(heredoc, hdoc_count);
	return (0);
}
