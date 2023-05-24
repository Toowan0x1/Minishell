/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/25 00:12:04 by oel-houm         ###   ########.fr       */
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
            pid_t pid;
            
            pid = fork();
            check_fork_fail(&pid);
            // execute_multi_cmds();
            init_cmd_data(cmd_data, line);
            expand(cmd_data->parsed_line_args, cmd_data->args_tokens, env_list);
            delete_quoate(cmd_data->parsed_line_args);
            if (pid == 0)
            {
                int i = 0;
                if (cmd_data->num_of_cmds > 1)
                {
                    while (i < cmd_data->num_of_cmds - 1)
                    {
                        int *cmd_tokens = tokenise_cmd(cmd_data->cmd[i]);
                        establish_output_stream(cmd_data->cmd[i], cmd_tokens, redirection); // init output stream + duping
                    	establish_input_stream(cmd_data->cmd[i], cmd_tokens, redirection);
                    	dup_output_before_piping(redirection);
		                dup_input_before_piping(redirection);
                        piping(cmd_data->cmd[i], STDIN, redirection->out_fd, env, env_list, cmd_data->args_tokens);
                        dup_output_after_piping(redirection);
                        i++;
                    }
                    int *cmd_tokens = tokenise_cmd(cmd_data->cmd[i]);
                    establish_output_stream(cmd_data->cmd[i], cmd_tokens, redirection); // init output stream + duping
                    establish_input_stream(cmd_data->cmd[i], cmd_tokens, redirection);
                    if (redirection->out_redirection_token == 0)
                        redirection->out_fd = cmd_data->stdout_copy;
                    else
                        redirection->out_fd = open(redirection->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
                    dup_output_before_piping(redirection);
		            dup_input_before_piping(redirection);
                    exec_cmd(cmd_data->cmd[i], env);
                    cmd_not_found(cmd_data->cmd[i][0], &global_exit);
                }
            }
            else
            {
                int status;
                waitpid(pid, &status, 0);
                // Handle child process exit status if needed
            }
            // parent process affection here 
            // execute_only_cmd
            if (cmd_data->num_of_cmds == 1)
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
        }
        line = readline(GREEN"minishell ▸ "WHITE);
    }
    return (global_exit);
}

// pwd makadirch exit