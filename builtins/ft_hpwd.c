/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hpwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:54 by mbenchah          #+#    #+#             */
/*   Updated: 2025/06/09 18:03:54 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_hpwd(char *str, int flg)
{
	static char	*pwd;

	if (str)
		pwd = ft_strdup_env(str);
	if (flg == 1)
		return (pwd);
	if (flg == 2)
		printf("%s\n", pwd);
	return (NULL);
}
