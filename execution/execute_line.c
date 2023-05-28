/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 01:50:48 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/28 04:02:47 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_line(t_cmd_data *cmd_data, t_redirection *redirection, t_env *env_list, char *line)
{
    env_list->env_dbl = convert_env(env_list);
	init_cmd_data(cmd_data, line);
    expand(cmd_data->parsed_line_args, cmd_data->args_tokens, env_list);
    delete_quoate(cmd_data->parsed_line_args);
    if (cmd_data->num_of_cmds > 1)
        multi_pipes_execution(cmd_data, redirection, env_list);
    if (cmd_data->num_of_cmds == 1)
        single_cmd_execution1(cmd_data, redirection, env_list);
    free_all_env(env_list->env_dbl);
}
