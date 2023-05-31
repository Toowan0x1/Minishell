/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 07:09:00 by oel-houm          #+#    #+#             */
/*   Updated: 2023/06/01 00:07:53 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_input_token_to_null(char **cmd, int *cmd_tokens)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd_tokens[i] == R_IN_SIG)
			cmd[i] = NULL;
		i++;
	}
}

int	get_input_redirection_index(int *cmd_tokens, t_redirection *redirection)
{
	int	i;

	i = 0;
	while (cmd_tokens[i])
	{
		if (cmd_tokens[i] == R_IN_SIG)
		{
			redirection->in_redirection_token = cmd_tokens[i];
			return (i);
		}
		i++;
	}
	return (0);
}

int	get_infile_index(int *cmd_tokens, int index)
{
	while (cmd_tokens[index])
	{
		if (cmd_tokens[index] == R_OUT_FILE || cmd_tokens[index] == R_APP_FILE)
			return (index);
		index++;
	}
	return (0);
}

void	establish_input_stream(char **cmd, int *cmd_tokens, \
			t_redirection *redirection)
{
	redirection->in_redirection_token = 0;
	redirection->in_redirection_index = -2;
	redirection->infile_index = -2;
	redirection->infile = NULL;
	redirection->in_fd = STDIN;
	redirection->stdin_copy = STDIN;
	redirection->stdout_copy = STDOUT;
	redirection->in_redirection_index = get_input_redirection_index(cmd_tokens, \
			redirection);
	redirection->infile_index = redirection->in_redirection_index + 1;
	redirection->infile = cmd[redirection->infile_index];
	if (redirection->in_redirection_index != -2 \
			&& redirection->infile_index != -2)
	{
		if (redirection->in_redirection_token == 3)
			redirection->in_fd = open(redirection->infile, O_RDONLY);
		if (redirection->in_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(redirection->infile);
			exit(1);
		}
	}
	set_input_token_to_null(cmd, cmd_tokens);
	if (redirection->infile != NULL && redirection->in_redirection_token == 3)
	{
		cmd[0] = NULL;
		cmd[1] = NULL;
		cmd[0] = cmd[2];
	}
}
