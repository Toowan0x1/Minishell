/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:59:33 by oel-houm          #+#    #+#             */
/*   Updated: 2023/06/01 00:03:10 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// set env_value on the specified env_name
void	set_env(char *env_name, char *env_value, t_env *env_list) // new_env_value 
{
	//size_t  i;
	int     env_len;
	char    *env;
	//char    *tmp;
	//char    *new;

	if (!env_name || !env_value)
		return ;
	env_len = ft_strlen(env_name);
	if (find_env(env_name, env_list) > 0)
	{
		while (env_list->env_name)
		{
			if (ft_strncmp(env_list->env_name, env_name, env_len) == 0)
			{
				free(env_list->env_value);
				env = ft_strdup(env_value); // leaks-fix
				env_list->env_value = env;
				break ;
			}
			env_list = env_list->next;
		}
	}
}
