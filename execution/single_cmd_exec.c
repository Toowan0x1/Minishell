/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:21:42 by oel-houm          #+#    #+#             */
/*   Updated: 2023/06/01 00:09:01 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_cmd_execution1(t_cmd_data *cmd_data, t_redirection *redirection,
			t_env *env_list)
{
	int				*cmd_tokens;
	t_heredoc_data	*heredoc_data;
	pid_t			pid;
	int				tmp;

	cmd_tokens = tokenise_cmd(cmd_data->cmd[0]);
	if (is_heredoc(cmd_data->cmd[0], cmd_tokens) == 1)
	{
		heredoc_data = malloc(sizeof(t_heredoc_data));
		init_heredoc_data(heredoc_data);
		get_heredoc_outfile_data(cmd_data->cmd[0], cmd_tokens, heredoc_data);
		get_heredoc_limiter(cmd_data->cmd[0], cmd_tokens, heredoc_data);
		set_heredoc_token_to_null(cmd_data->cmd[0], cmd_tokens);
		pid = fork();
		if (pid == 0)
		{
			if (heredoc_data->output_redir_token == R_OUT_SIG)
			{
				tmp = open(heredoc_data->outfile, O_TRUNC
						| O_CREAT | O_WRONLY, 0644);
				close(tmp);
			}
			piping_heredoc(heredoc_data);
			if (cmd_tokens[0] == CMD_NAME)
				exec_cmd(cmd_data->cmd[0], env_list->env_dbl);
			exit(0);
		}
		else
			wait(&pid);
	}
	else if (is_builtins(cmd_data->cmd[0][0]) == 1)
	{
		establish_io_stream(cmd_data->cmd[0], cmd_tokens, redirection);
		pid = fork();
		if (pid == 0)
		{
			dup2(redirection->out_fd, STDOUT);
			dup2(redirection->in_fd, STDIN);
			exec_builtins(cmd_data->cmd[0], cmd_data->args_tokens, env_list);
		}
		else if (pid > 0)
			wait(&pid);
	}
	else
	{
		establish_io_stream(cmd_data->cmd[0], cmd_tokens, redirection);
		pid = fork();
		if (pid == 0)
		{
			dup2(redirection->out_fd, STDOUT);
			dup2(redirection->in_fd, STDIN);
			exec_cmd(cmd_data->cmd[0], env_list->env_dbl);
		}
		else if (pid > 0)
			wait(&pid);
	}
}
