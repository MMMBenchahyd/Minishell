/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:02:16 by mbenchah          #+#    #+#             */
/*   Updated: 2025/06/09 18:02:16 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_child_io(int fd_in, int *fd, t_cmd cmd, char **heredoc)
{
	if (fd_in != STDIN_FILENO)
	{
		ft_dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (!cmd.last && ft_dup2(fd[1], STDOUT_FILENO) == -1)
		ft_exit(EXIT_FAILURE);
	if (!cmd.last)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (ft_redirection(&cmd, heredoc, cmd.hdoc_indx))
		ft_exit(EXIT_FAILURE);
}

static void	execute_cmd(t_cmd cmd)
{
	if (!cmd.tokens[0])
		ft_exit(EXIT_SUCCESS);
	if (!ft_strcmp("exit", cmd.tokens[0]->value))
		exit_builtin(cmd, 0);
	else if (is_builtin(cmd))
		ft_exit(exec_builtin(cmd));
	ft_execve(cmd);
}

int	exec_bin(t_cmd cmd, int fd_in, char **heredoc, int *last_pid)
{
	int	fd[2];
	int	pid;

	ft_set_read_stat(0);
	if (!cmd.last && pipe(fd) == -1)
		return (perror("minishell: pipe"), EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_child_io(fd_in, fd, cmd, heredoc);
		execute_cmd(cmd);
	}
	*last_pid = pid;
	if (!cmd.last)
		close(fd[1]);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	return (fd[0]);
}
