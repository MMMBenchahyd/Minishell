/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:52:51 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:52:52 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_cd_error(char *path, char *msg)
{
	char		*cnct;
	const char	*default_error = "error retrieving current directory: "
		"getcwd: cannot access parent directories: "
		"No such file or directory\n";

	cnct = "minishell: cd: ";
	if (path)
		cnct = ft_strjoin(cnct, ft_strjoin(path, ": "));
	if (msg)
		cnct = ft_strjoin(cnct, msg);
	else
		cnct = ft_strjoin("cd: ", default_error);
	ft_putstr_fd(cnct, STDERR_FILENO);
}

static void	update_oldpwd(void)
{
	char	*current_pwd;

	current_pwd = ft_getenv("PWD");
	if (ft_envchr("OLDPWD"))
		ft_update_env("OLDPWD", current_pwd);
	else
		ft_lstadd_back_env(ft_lstnew_env("OLDPWD", "=", current_pwd));
}

static void	update_pwd(char *new_path)
{
	if (ft_envchr("PWD"))
		ft_update_env("PWD", new_path);
	else
		ft_lstadd_back_env(ft_lstnew_env("PWD", "=", ft_strdup_env(new_path)));
}

static void	update_path_vars(char *new_pwd)
{
	ft_hpwd(new_pwd, 0);
	update_oldpwd();
	update_pwd(new_pwd);
}

int	ft_chdir(char *path)
{
	char		current_path[PATH_MAX];
	static char	*tmp;

	if (ft_strlen(path) > PATH_MAX)
	{
		print_cd_error(path, "Path too long\n");
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		perror(ft_strjoin("minishell: cd: ", path));
		return (EXIT_FAILURE);
	}
	if (getcwd(current_path, PATH_MAX))
		update_path_vars(current_path);
	else if (!ft_strcmp(path, ".."))
	{
		tmp = ft_strjoin_env(tmp, "/..");
		ft_hpwd(ft_strjoin(ft_hpwd(0, 1), "/.."), 0);
		return (print_cd_error(0, 0), EXIT_FAILURE);
	}
	return (tmp = 0, EXIT_SUCCESS);
}
