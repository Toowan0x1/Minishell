/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_0x0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 02:02:05 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/27 08:33:39 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_heredoc_data(t_heredoc_data *heredoc_data)
{
	heredoc_data->limiter = NULL;
	heredoc_data->outfile = NULL;
	heredoc_data->output_redir_token = 0;
}

int	is_heredoc(char **cmd, int *cmd_token)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd_token[i] == HEREDOC_SIG && cmd_token[i + 1] == HEREDOC_LIM)
			return (1);
		i++;
	}
	return (0);
}

void	set_heredoc_token_to_null(char **cmd, int *cmd_token)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd_token[i] == HEREDOC_SIG)
		{
			cmd[i] = NULL;
			break ;
		}
		i++;
	}
	return ;
}

void	get_heredoc_limiter(char **cmd, int *cmd_token, \
							t_heredoc_data *heredoc_data)
{
	int	i;

	heredoc_data->limiter = NULL;
	i = 0;
	while (cmd[i])
	{
		if (cmd_token[i] == HEREDOC_SIG)
		{
			heredoc_data->limiter = cmd[i + 1];
			break ;
		}
		i++;
	}
	return ;
}

void	get_heredoc_outfile_data(char **cmd, int *cmd_token, \
									t_heredoc_data *heredoc_data)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd_token[i] == R_APP_SIG || cmd_token[i] == R_OUT_SIG)
		{
			heredoc_data->output_redir_token = cmd_token[i];
			i++;
			if (cmd_token[i] == R_APP_FILE || cmd_token[i] == R_OUT_FILE)
			{
				heredoc_data->outfile = cmd[i];
				break ;
			}
		}
		i++;
	}
	return ;
}
