/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:21:15 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/31 23:48:48 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h> // for errno, ENOMEM, ERANGE

void	pwd_cmd(char **line)
{
	char	*cwd;

	(void)line;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (errno == ENOMEM)
			ft_putstr_fd("pwd: out of memory\n", 2);
		else if (errno == ERANGE)
			ft_putstr_fd("pwd: path name too long\n", 2);
		else
			perror("pwd: getcwd error");
		return ;
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
}
