/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:48:38 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 22:27:54 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    dup_input_before_piping(t_redirection *redirection)
{
        if (redirection->in_fd != STDIN)
                dup2(redirection->in_fd, STDIN);
        else
                redirection->in_fd = STDIN;
}

void    dup_input_after_piping(t_redirection *redirection)
{
        if (redirection->in_fd != STDIN)
                redirection->in_fd = STDIN;
}
