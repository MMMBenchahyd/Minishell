/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_in_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:16 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 01:26:22 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_execve_err(char *bin, char *msg)
{
	char	*str;

	str = ft_strjoin("minishell: ", bin);
	str = ft_strjoin(str, ": ");
	str = ft_strjoin(str, msg);
	str = ft_strjoin(str, "\n");
	ft_putstr_fd(str, STDERR_FILENO);
}

static int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

static int	check_valid_cmd(char *bin)
{
	if (!bin)
		return (0);
	if (access(bin, F_OK) != 0)
	{
		print_execve_err(bin, strerror(errno));
		return (ft_set_status(127), 0);
	}
	if (is_directory(bin) || bin[ft_strlen(bin) - 1] == '/')
	{
		print_execve_err(bin, "Is a directory");
		return (ft_set_status(126), 0);
	}
	if (access(bin, X_OK) != 0)
	{
		print_execve_err(bin, "Permission denied");
		return (ft_set_status(126), 0);
	}
	return (1);
}

char	*get_cmd_path(char *bin)
{
	char	*path;
	char	**split;
	char	*result;

	split = NULL;
	if (!bin || !*bin)
		return (NULL);
	if (!ft_strcmp(bin, ".") || !ft_strcmp(bin, ".."))
	{
		print_execve_err(bin, "command not found");
		return (ft_set_status(127), NULL);
	}
	if (bin[0] == '/' || !ft_strncmp(bin, "./", 2)
		|| !ft_strncmp(bin, "../", 3))
	{
		if (check_valid_cmd(bin))
			return (bin);
		return (NULL);
	}
	path = ft_getenv("PATH");
	if (path)
		split = ft_split(path, ':');
	result = search_in_path(bin, split);
	return (result);
}

char	*search_in_path(char *bin, char **path_dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs && path_dirs[i])
	{
		full_path = ft_strjoin(ft_strjoin(path_dirs[i], "/"), bin);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	if (!path_dirs)
		return (ft_strjoin("./", bin));
	print_execve_err(bin, "command not found");
	ft_set_status(127);
	return (NULL);
}
