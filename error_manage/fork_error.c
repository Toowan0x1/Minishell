/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:58:36 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 01:00:29 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_fork_fail(pid_t *pid)
{
	if (pid < 0)
	{
		perror("Fork error");
		exit(1);
	}
}
