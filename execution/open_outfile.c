/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:47:13 by oel-houm          #+#    #+#             */
/*   Updated: 2023/06/01 00:08:34 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_output_token_to_null(char **cmd, int *cmd_tokens)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd_tokens[i] == R_OUT_SIG || cmd_tokens[i] == R_APP_SIG)
			cmd[i] = NULL;
		i++;
	}
}

int	get_output_redirection_index(int *cmd_tokens, t_redirection *redirection)
{
	int	i;

	i = 0;
	while (cmd_tokens[i])
	{
		if (cmd_tokens[i] == 4 || cmd_tokens[i] == 7)
		{
			redirection->out_redirection_token = cmd_tokens[i];
			return (i);
		}
		i++;
	}
	return (0);
}

int	get_outfile_index(int *cmd_tokens, int index)
{
	while (cmd_tokens[index])
	{
		if (cmd_tokens[index] == 5 || cmd_tokens[index] == 8)
			return (index);
		index++;
	}
	return (0);
}

void	establish_output_stream(char **cmd, int *cmd_tokens, \
		t_redirection *redirection)
{
	redirection->out_redirection_token = 0;
	redirection->out_redirection_index = 0;
	redirection->outfile_index = 0;
	redirection->outfile = NULL;
	redirection->out_fd = STDOUT;
	redirection->stdin_copy = STDIN;
	redirection->stdout_copy = STDOUT;
	redirection->out_redirection_index = \
			get_output_redirection_index(cmd_tokens, redirection);
	redirection->outfile_index = get_outfile_index(cmd_tokens, \
			redirection->out_redirection_index);
	redirection->outfile = cmd[redirection->outfile_index];
	if (redirection->out_redirection_index != 0
		&& redirection->outfile_index != 0)
	{
		if (redirection->out_redirection_token == 4)
			redirection->out_fd = open(redirection->outfile, O_TRUNC
					| O_WRONLY | O_CREAT, 0644);
		else if (redirection->out_redirection_token == 7)
			redirection->out_fd = open(redirection->outfile, O_APPEND
					| O_WRONLY | O_CREAT, 0644);
		if (redirection->out_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(redirection->infile);
			exit(1);
		}
	}
	set_output_token_to_null(cmd, cmd_tokens); // set output token to null
}

/*
 * pwd | < minishell.c cat | wc
 * if the cmd[0] == <  then do establish_input_stream() and open file then set cmd[0] = the cmd[2]
 * < minishell.c cat dsfdsf | head
 * if < kanakhod argg li morah as infile
 * manakhod arg li mora infile as cmd o mandir liha ckeck if the cmd ixist or not ila la kandir perror and exit
 * ila kan chi arg mora cmd kanmchi nchof wach howa file and wach it exist ila ah kanrj3o howa li infile

 * < file1 cat file2 file1

 * if infile and i == 0

 * pwd | < makefile catdf | head
 

*/
