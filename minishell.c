/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/06/01 00:50:44 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_env			*env_list;
	t_redirection	*redirection;
	t_cmd_data		*cmd_data;

	(void)av;
	check_argc(ac);
	g_exit = 0;
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
			execute_line(cmd_data, redirection, env_list, line);
		line = readline(GREEN"minishell ▸ "WHITE);
	}
	return (g_exit);
}

	/*	test env here	*/ 
	//char **env_arr = convert_env(env_list);
	//(void)env_arr;

	/*
	conver_env() => char **env
	execve(path, cmd_args, env);
	env_free_all();
	*/

	// env export unset exit | leaks loop | env converts | norm 
	//| add expand to multi_cmd | c
	//at cat cat ls | err management | signal | minishell.h | read

	// int i=0;
	// //int j=0;
	// while (env_arr[i])
	// {
	// 	// while (env_arr[i][j])
	// 	// {
	// 	// 	j++;
	// 	// }
	// 	printf("[*] %s\n", env_arr[i]);
	// 	//printf("\n");
	// 	i++;
	// }
	// /*	the end	 */
