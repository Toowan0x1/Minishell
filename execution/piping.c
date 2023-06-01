/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:19:50 by oel-houm          #+#    #+#             */
/*   Updated: 2023/06/01 22:45:53 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    piping(char **cmd, int infile, int outfile, t_env *env_list, int *token)
{
	int	fd[2];
	int	pid;
	int	status;
	(void)token;
	pipe(fd);
	pid = fork();
	check_fork_fail(&pid);
	if (pid == 0)
	{
		dup2(fd[1], outfile);
		close(fd[0]);
		close(fd[1]);
		if (is_builtins(cmd[0]) == 1)
		{
			exec_builtins(cmd, token, env_list);
			exit(0);
		}
		else
			exec_cmd(cmd, env_list->env_dbl);
	}
	dup2(fd[0], infile);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit = WEXITSTATUS(status);
		//printf("Child process exited with status: %d\n", g_exit);
		// Handle exit status as needed
	}
	else
	{
        //printf("Child process terminated abnormally\n");
        // Handle abnormal termination as needed
	}
}
