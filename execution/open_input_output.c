/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_input_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:51:03 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/27 10:54:20 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	establish_io_stream(char **cmd, int *cmd_tokens, t_redirection *redirection)
{
	establish_output_stream(cmd, cmd_tokens, redirection);
	establish_input_stream(cmd, cmd_tokens, redirection);
}
