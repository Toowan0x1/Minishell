/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fails.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 06:40:08 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/27 06:40:13 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_fork_fail(pid_t *pid)
{
	if (*pid < 0)
	{
		perror("fork");
		exit(1);
	}
}

void	check_dup2_fail(int *ret)
{
	if (*ret == -1)
	{
		perror("dup2");
		exit(1);
	}
}

void	check_pipe_fail(int *ret)
{
	if (*ret == -1)
	{
		perror("pipe");
		exit(1);
	}
}
