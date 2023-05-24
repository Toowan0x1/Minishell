/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:21:10 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/24 07:53:06 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multi_pipes_execution(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list)
{
	int	i;

	i = 0;
	while (i < cmd_data->num_of_cmds - 1)
    { // problem is here
        cmd_data->cmd_tokens = tokenise_cmd(cmd_data->cmd[i]);
        // out & in establish and init
        // dup io before piping
        // dup io after piping
        establish_output_stream(cmd_data->cmd[i], cmd_data->cmd_tokens, redirection); // init output stream + duping
        establish_input_stream(cmd_data->cmd[i], cmd_data->cmd_tokens, redirection);
        dup_output_before_piping(redirection);
		dup_input_before_piping(redirection);
        //ft_putstr_fd(cmd_data->cmd[i][0], 1);
        piping(cmd_data->cmd[i], redirection->in_fd, redirection->out_fd, env, env_list, cmd_data->args_tokens);
        dup_output_after_piping(redirection);
        dup_input_after_piping(redirection);
    //printf("== %s %s %s in=%d out=%d\n", redirection->infile, redirection->outfile, cmd_data->cmd[i][0], redirection->in_fd, redirection->out_fd);
		i++;
    }
    cmd_data->cmd_tokens = tokenise_cmd(cmd_data->cmd[i]);
    establish_output_stream(cmd_data->cmd[i], cmd_data->cmd_tokens, redirection);
    establish_input_stream(cmd_data->cmd[i], cmd_data->cmd_tokens, redirection);
    dup2(redirection->out_fd, STDOUT);
    dup2(redirection->in_fd, STDIN);
    exec_cmd(cmd_data->cmd[i], env);
    cmd_not_found(cmd_data->cmd[i][0], &global_exit);
}
// pwd | cat > out | ls > lolo
// if outfile == null then redirect to outfile stdout

// pwd | < minishell.c head | wc > lolo | ls > popo
//                       -> ! ->
// head minishell.c | < Makefile  head | wc > here | cat
// head minishell.c | cat | cat | cat > haha | ls