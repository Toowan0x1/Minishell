/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/21 18:00:35 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int global_exit;

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char    *line;
    t_env   *env_list;
    if (ac > 1)
    {
        ft_putstr_fd("Error: too many arguments\n", 2);
        return (127);
    }
    env_list = create_env_list(env);
    line = readline(GREEN"minishell ▸ "WHITE);
    int walid = 1;
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
                (void)env_list;
                char **parsed_line_args;
                int num_of_cmds;
                int *args_tokens;
                char ***cmd;
                int i;
                int out_fd = STDOUT;
                int stdout_copy = dup(STDOUT);
                int stdin_copy = dup(STDIN);
                (void)stdin_copy;
                
                // sort this 
                line = parse_operator(line);
                parsed_line_args = args_split(line);
                num_of_cmds = count_cmds(parsed_line_args, '|');
                args_tokens = tokenise_cmd(parsed_line_args);
                if (walid == 1)
                {
                    //printf("======= before expand =========\n");
                    expand(parsed_line_args, args_tokens, env_list);  // !!!!!
                }
                cmd = get_piped_cmd_by_ptr(parsed_line_args, args_tokens);
                i = 0;
                if (num_of_cmds > 1)
                {
                    while (i < num_of_cmds - 1)
                    {
                        /*/*/
                        int     *cmd_tokens;
                        cmd_tokens = tokenise_cmd(cmd[i]);
                        int x = 0;
                        //int count_outfile = 0;
                        int redir_token; // fih token >, >>
                        int redir_index = 0; // fih index dyal token >, >>
                        int redir_outfile_index = 0; // fih outfile index
                        //int out_fd = STDOUT;    // out file descriptor
                        while (cmd_tokens[x])
                        {
                            if (cmd_tokens[x] == 4 || cmd_tokens[x] == 7)
                            {
                                redir_token = cmd_tokens[x];
                                redir_index = x;
                            }
                            x++;
                        }
                        x = redir_index;
                        while (cmd_tokens[x])
                        {
                            if (cmd_tokens[x] == 5 || cmd_tokens[x] == 8)
                            {
                                redir_outfile_index = x;
                            }
                            x++;
                        }
                        char *outfile = cmd[i][redir_outfile_index];
                        if (redir_index != 0 && redir_outfile_index != 0)
                        {
                            if (redir_token == 4)
                                out_fd = open(outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
                            else if (redir_token == 7)
                                out_fd = open(outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
                            //printf("outfile is %s\n", cmd[0][redir_outfile_index]);
                        }
                        // set redir b null
                        x = 0;
                        while (cmd[i][x])
                        {
                            if (cmd_tokens[x] == 4 || cmd_tokens[x] == 7)
                            {
                                cmd[i][x] = NULL;
                            }
                            x++;
                        }


                
                        if (out_fd != STDOUT)
                        {
                            dup2(out_fd, STDOUT);
                        }
                        else
                            out_fd = STDOUT;
                        // int h = i;
                        // int p = 0;
                        // while (cmd[h])
                        // {
                        //     while (cmd[h][p] != NULL)
                        //     {
                        //         printf("cmd = %s\n", cmd[h][p]);
                        //         p++;
                        //     }
                        //     h++;
                        // }
                        piping(cmd[i], STDIN, out_fd, env, env_list, args_tokens);
                        if (out_fd != STDOUT)
                        {
                            out_fd = STDOUT;
                        }
                        i++;
                    }
                    dup2(stdout_copy, STDOUT);
                    exec_cmd(cmd[i], env);
                    ft_putstr_fd("minishell: ", 2);
                    ft_putstr_fd(cmd[i][0], 2);
                    ft_putstr_fd(": command not found\n", 2);
                    global_exit = 127;
                    exit(127);
                }
                //parse_cmd(s, t, env_list);
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
            if (num_of_cmds == 1)
            {
                int     *cmd_tokens;
                cmd_tokens = tokenise_cmd(cmd[0]);
                int x = 0;
                //int count_outfile = 0;
                int redir_token; // fih token >, >>
                int redir_index = 0; // fih index dyal token >, >>
                int redir_outfile_index = 0; // fih outfile index
                int out_fd = STDOUT;    // out file descriptor
                while (cmd_tokens[x])
                {
                    if (cmd_tokens[x] == 4 || cmd_tokens[x] == 7)
                    {
                        redir_token = cmd_tokens[x];
                        redir_index = x;
                    }
                    x++;
                }
                x = redir_index;
                while (cmd_tokens[x])
                {
                    if (cmd_tokens[x] == 5 || cmd_tokens[x] == 8)
                    {
                        redir_outfile_index = x;
                    }
                    x++;
                }
                char *outfile = cmd[0][redir_outfile_index];
                if (redir_index != 0 && redir_outfile_index != 0)
                {
                    if (redir_token == 4)
                        out_fd = open(outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
                    else if (redir_token == 7)
                        out_fd = open(outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
                    //printf("outfile is %s\n", cmd[0][redir_outfile_index]);
                }
                // set redir b null
                x = 0;
                while (cmd[0][x])
                {
                    if (cmd_tokens[x] == 4 || cmd_tokens[x] == 7)
                    {
                        cmd[0][x] = NULL;
                    }
                    x++;
                }
                    
                if (is_builtins(cmd[0][0]) == 1)
                {
                    int ps = fork();
                    if (ps == 0)
                    {
                        dup2(out_fd, STDOUT);
                        exec_builtins(cmd[0], args_tokens, env_list); // kayb9a mhangi ila ma exsitach process
                        exit(0); // handle exit f builtins // 
                    }
                    else if (ps > 0)
                    {
                        wait(&ps);
                    }
                }
                else
                {
                    int ps = fork();
                    if (ps == 0)
                    {
                        dup2(out_fd, STDOUT);
                        exec_cmd(cmd[0], env);
                    }
                    else if (ps > 0)
                    {
                        wait(&ps);
                    }
                }
            }
        }
        walid++;
        line = readline(GREEN"minishell ▸ "WHITE);
    }
    return (global_exit);
}