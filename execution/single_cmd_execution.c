/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:21:42 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/26 19:01:47 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int     is_heredoc(char **cmd, int *cmd_token)
{
    int i;

    i = 0;
    while(cmd[i] != NULL)
    {
        if (cmd_token[i] == 10)
        {
            if (cmd_token[i + 1] != 0)
                return (1);
        }
        i++;
    }
    return (0);
}

char     *get_heredoc_limiter(char **cmd, int *cmd_token)
{
    int i;

    i = 0;
    while(cmd[i] != NULL)
    {
        if (cmd_token[i] == 10)
        {
            if (cmd_token[i + 1] != 0)
                return (cmd[i + 1]);
        }
        i++;
    }
    return NULL;
}

char     *get_heredoc_outfile(char **cmd, int *cmd_token)
{
    int i;

    i = 0;
    while(cmd[i] != NULL)
    {
        if (cmd_token[i] == 10)
        {
            if (cmd_token[i + 2] != 0)
                return (cmd[i]);
        }
        else
            return (NULL);
        i++;
    }
    return (NULL);
}

////// 

void	write_heredoc(char *limiter, int fd[2])
{
	int	limiter_len;
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN);
        limiter_len = ft_strlen(limiter);
		if (!line)
		{
			close(fd[0]);
			close(fd[1]);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(line, limiter, limiter_len) == 0 && !line[limiter_len + 1])
		{
			close(fd[0]);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = NULL;
	}
}

void	piping_heredoc(char *limiter)
{
	pid_t	ps;
	int		fd[2];

	pipe(fd);
	ps = fork();
	if (ps)
	{
		dup2(fd[0], STDIN);
		close(fd[0]);
		close(fd[1]);
		waitpid(ps, NULL, 0);
	}
	else if (ps == 0)
		write_heredoc(limiter, fd);
}

void    set_heredoc_token_to_null(char **cmd, int *cmd_token)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd_token[i] == 10)
            cmd[i] = NULL;
        i++;
    }
}

void    single_cmd_execution1(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list)
{
    int *cmd_tokens = tokenise_cmd(cmd_data->cmd[0]);
    establish_io_stream(cmd_data->cmd[0], cmd_tokens, redirection);


    if (is_heredoc(cmd_data->cmd[0], cmd_tokens) == 1)
    {
        char *heredoc_limiter;
        int heredoc_outfile_fd;

        int pid = fork();
        if (pid == 0){
        heredoc_limiter = ft_strdup(get_heredoc_limiter(cmd_data->cmd[0], cmd_tokens));
        if (get_heredoc_outfile(cmd_data->cmd[0], cmd_tokens) == NULL)
            heredoc_outfile_fd = STDOUT;
        else
        {
            heredoc_outfile_fd = open(ft_strdup(get_heredoc_outfile(cmd_data->cmd[0], cmd_tokens)), O_TRUNC | O_CREAT | O_WRONLY, 0644); // append
        }
        piping_heredoc(heredoc_limiter);
        set_heredoc_token_to_null(cmd_data->cmd[0], cmd_tokens);
        exec_cmd(cmd_data->cmd[0], env);
        exit(0);
        }else{
            wait(&pid);
        }
        //dup2(heredoc_outfile_fd, STDOUT);
        //dup2(STDIN, STDIN);
        // char **line;
        // while (1)
        // {
        //     ft_putstr_fd("minishell heredoc> ", STDOUT);
		//     line = get_next_line(STDIN);
        // }
    }
    
    else if (is_builtins(cmd_data->cmd[0][0]) == 1)
    {
        int pid = fork();
        if (pid == 0)
        {
            dup2(redirection->out_fd, STDOUT);
            dup2(redirection->in_fd, STDIN);
            exec_builtins(cmd_data->cmd[0], cmd_data->args_tokens, env_list); // kayb9a mhangi ila ma exsitach process
        }
        else if (pid > 0)
            wait(&pid);
    }
    else
    {
        int pid = fork();
        if (pid == 0)
        {
            dup2(redirection->out_fd, STDOUT);
            dup2(redirection->in_fd, STDIN);
            exec_cmd(cmd_data->cmd[0], env);
        }
        else if (pid > 0)
            wait(&pid);
    }
}
