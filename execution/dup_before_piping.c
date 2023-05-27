/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_before_piping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 06:58:30 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/27 07:00:37 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_output_before_piping(t_redirection *redirection)
{
	if (redirection->out_fd != STDOUT)
		dup2(redirection->out_fd, STDOUT);
	else
		redirection->out_fd = STDOUT;
}

void	dup_input_before_piping(t_redirection *redirection)
{
	if (redirection->in_fd != STDIN)
		dup2(redirection->in_fd, STDIN);
	else
		redirection->in_fd = STDIN;
}

void	dup_io_before_piping(t_redirection *redirection)
{
	dup_output_before_piping(redirection);
	dup_input_before_piping(redirection);
}
