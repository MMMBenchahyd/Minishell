/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanbadi <aanbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:25 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/09 17:48:26 by aanbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_builtin(t_cmd cmd)
{
	char	path[PATH_MAX];

	(void)cmd;
	if (getcwd(path, PATH_MAX))
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	ft_hpwd(0, 2);
	return (EXIT_FAILURE);
}
