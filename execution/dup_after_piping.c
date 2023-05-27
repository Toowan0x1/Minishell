/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_after_piping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 07:01:00 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/27 08:32:06 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_output_after_piping(t_redirection *redirection)
{
	if (redirection->out_fd != STDOUT)
		redirection->out_fd = STDOUT;
}

void	dup_input_after_piping(t_redirection *redirection)
{
	if (redirection->in_fd != STDIN)
		redirection->in_fd = STDIN;
}

void	dup_io_after_piping(t_redirection *redirection)
{
	dup_output_after_piping(redirection);
	dup_input_input_piping(redirection);
}
