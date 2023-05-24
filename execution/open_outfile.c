/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:47:13 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/24 07:38:55 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_output_redirect_to_null(char **cmd, int *cmd_tokens)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd_tokens[i] == 4 || cmd_tokens[i] == 7) // || cmd_tokens[i] == 0 || cmd_tokens[i] == 0
			cmd[i] = NULL;
		i++;
	}
}

int		get_output_redirection_index(int *cmd_tokens, t_redirection *redirection)
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
	return (0); // return ;
}

int		get_outfile_index(int *cmd_tokens, int index)
{
	while (cmd_tokens[index])
	{
		if (cmd_tokens[index] == 5 || cmd_tokens[index] == 8)  //// !!! may be
        {
            return (index);
        }
		index++;
	}
	return (0); // return ;
}

void	establish_output_stream(char **cmd, int *cmd_tokens, t_redirection *redirection)
{
	redirection->out_redirection_token = 0;
	redirection->out_redirection_index = 0;
	redirection->outfile_index = 0;
	redirection->outfile = NULL;
	redirection->out_fd = STDOUT;
	
	redirection->stdin_copy = STDIN;
	redirection->stdout_copy = STDOUT;

	redirection->out_redirection_index = get_output_redirection_index(cmd_tokens, redirection);
	redirection->outfile_index = get_outfile_index(cmd_tokens, redirection->out_redirection_index);
	redirection->outfile = cmd[redirection->outfile_index];
	if (redirection->out_redirection_index != 0 && redirection->outfile_index != 0)
	{
		if (redirection->out_redirection_token == 4)
			redirection->out_fd = open(redirection->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		else if (redirection->out_redirection_token == 7)
			redirection->out_fd = open(redirection->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (redirection->out_fd == -1)
    	{
        	ft_putstr_fd("minishell: ", 2);
            perror(redirection->infile); // no such file or dir ????????
            exit(1);
    	}
	}
	set_output_redirect_to_null(cmd, cmd_tokens); // set output token to null
}
