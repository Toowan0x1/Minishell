/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/22 22:33:09 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int global_exit;

int main(int ac, char **av, char **env)
{
    (void)av;
    char    *line;
    t_env   *env_list;
    check_argc(ac);
    env_list = create_env_list(env);
    t_redirection *redirection;
    redirection = malloc(sizeof(t_redirection));

    line = readline(GREEN"minishell ▸ "WHITE);
    //global_exit = 0;
    while (1)
    {
        if (line)
            add_history(line);
        else
            return (0); // handle ctrl + d
        if (parse(line))
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("Fork error");
                exit(1);
            }
            else if (pid == 0)
            {
                char **parsed_line_args;
                int num_of_cmds;
                int *args_tokens;
                char ***cmd;
                int i;
                int stdout_copy = dup(STDOUT);
                int stdin_copy = dup(STDIN);
                (void)stdin_copy;
                
                // sort this 
                line = parse_operator(line);
                parsed_line_args = args_split(line);
                num_of_cmds = count_cmds(parsed_line_args, '|');
                args_tokens = tokenise_cmd(parsed_line_args);
                cmd = get_piped_cmd_by_ptr(parsed_line_args, args_tokens);
                i = 0;
                // execute_multi_cmds()
                if (num_of_cmds > 1)
                {
                    while (i < num_of_cmds - 1)
                    {
                        int *cmd_tokens = tokenise_cmd(cmd[i]);
                        establish_output_stream(cmd[i], cmd_tokens, redirection); // init output stream + duping
                        dup_output_before_piping(redirection);
                        piping(cmd[i], STDIN, redirection->out_fd, env, env_list, args_tokens);
                        dup_output_after_piping(redirection);
                        i++;
                    }
                    dup2(stdout_copy, STDOUT);
                    exec_cmd(cmd[i], env);
                    cmd_not_found(cmd[i][0], &global_exit);
                }
            }
            else
            {
                int status;
                waitpid(pid, &status, 0);
                // Handle child process exit status if needed
            }
            // parent process affection here 
            char **parsed_line_args;
            int *args_tokens;
            char ***cmd;
            int num_of_cmds;
            line = parse_operator(line);
            parsed_line_args = args_split(line);
            num_of_cmds = count_cmds(parsed_line_args, '|');
            args_tokens = tokenise_cmd(parsed_line_args);
            cmd = get_piped_cmd_by_ptr(parsed_line_args, args_tokens);
            // execute_only_cmd
            if (num_of_cmds == 1)
            {

                /*
                dup_output_before_piping(redirection);
                piping(cmd[i], STDIN, redirection->out_fd, env, env_list, args_tokens);
                dup_output_after_piping(redirection);
                */
                int *cmd_tokens = tokenise_cmd(cmd[0]);
                establish_output_stream(cmd[0], cmd_tokens, redirection);
                if (is_builtins(cmd[0][0]) == 1)
                {
                    int pid = fork();
                    if (pid == 0)
                    {
                        dup2(redirection->out_fd, STDOUT);
                        exec_builtins(cmd[0], args_tokens, env_list); // kayb9a mhangi ila ma exsitach process
                        exit(0); // handle exit f builtins // 
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
                        exec_cmd(cmd[0], env);
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