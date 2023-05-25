/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/25 01:46:36 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int global_exit;

void	init_cmd_data(t_cmd_data *cmd_data, char *line)
{
	line = parse_operator(line);
	cmd_data->parsed_line_args = args_split(line);
	cmd_data->num_of_cmds = count_cmds(cmd_data->parsed_line_args, '|');;
	cmd_data->args_tokens = tokenise_cmd(cmd_data->parsed_line_args);;
	cmd_data->cmd = get_piped_cmd_by_ptr(cmd_data->parsed_line_args, cmd_data->args_tokens);
	cmd_data->stdout_copy = dup(STDOUT);;
	cmd_data->stdin_copy = dup(STDIN);
	cmd_data->i = 0;
	(void)cmd_data->stdin_copy;
}

void    single_cmd_execution1(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list)
{
    int *cmd_tokens = tokenise_cmd(cmd_data->cmd[0]);
                establish_output_stream(cmd_data->cmd[0], cmd_tokens, redirection);
                establish_input_stream(cmd_data->cmd[0], cmd_tokens, redirection);
                if (is_builtins(cmd_data->cmd[0][0]) == 1)
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

int main(int ac, char **av, char **env)
{
    // initiate_values(T_DATA);
    char            *line;
    t_env           *env_list;
    t_redirection   *redirection;
    t_cmd_data      *cmd_data;
    
    (void)av;
    check_argc(ac);
    global_exit = 0;
    env_list = create_env_list(env);
    redirection = malloc(sizeof(t_redirection));
    cmd_data = malloc(sizeof(t_cmd_data));
    line = readline(GREEN"minishell ▸ "WHITE);
    while (1)
    {
        if (line)
            add_history(line);
        else
            write(1, "\n", 1);
        if (parse(line))
        {
            // execute_multi_cmds();
            init_cmd_data(cmd_data, line);
            expand(cmd_data->parsed_line_args, cmd_data->args_tokens, env_list);
            delete_quoate(cmd_data->parsed_line_args);
            if (cmd_data->num_of_cmds > 1)
            {
                multi_pipes_execution(cmd_data, redirection, env, env_list);
            }
            if (cmd_data->num_of_cmds == 1)
                single_cmd_execution1(cmd_data, redirection, env, env_list);
        }
        line = readline(GREEN"minishell ▸ "WHITE);
    }
    return (global_exit);
}

// pwd makadirch exit


