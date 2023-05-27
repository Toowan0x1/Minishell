/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_0x1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 02:33:28 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/27 08:33:27 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_heredoc_io(char *line, t_heredoc_data *heredoc_data, \
	int limiter_len, int fd[2])
{
	int	dup_ret;
	int	outfd;

	if (!line)
	{
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(line, heredoc_data->limiter, limiter_len) == 0
		&& !line[limiter_len + 1])
	{
		close(fd[0]);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	if (heredoc_data->outfile != NULL)
	{
		outfd = open(heredoc_data->outfile, O_CREAT | O_WRONLY | \
				O_APPEND, 0644);
		dup_ret = dup2(outfd, fd[1]);
		check_dup2_fail(&dup_ret);
	}
}

static void	write_heredoc(t_heredoc_data *heredoc_data, int fd[2])
{
	int		limiter_len;
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN);
		limiter_len = ft_strlen(heredoc_data->limiter);
		handle_heredoc_io(line, heredoc_data, limiter_len, fd);
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = NULL;
	}
}

void	piping_heredoc(t_heredoc_data *heredoc_data)
{
	pid_t	pid;
	int		fd[2];
	int		pipe_ret;

	pipe(fd);
	check_pipe_fail(&pipe_ret);
	pid = fork();
	check_fork_fail(&pid);
	if (pid)
	{
		dup2(fd[0], STDIN);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
	else if (pid == 0)
		write_heredoc(heredoc_data, fd);
}
