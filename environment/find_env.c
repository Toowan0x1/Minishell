/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:59:18 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/26 23:22:52 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_env(char *env, t_env *env_list)
{
	size_t	i;
	int		len;

	len = ft_strlen(env);
	i = 1;
	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->env_name, env, len) == 0)
		{
			if (ft_strncmp(&env_list->env_name[len + 1], "=", 0) == 0)
				return (i);
			i++;
		}
		else
			i++;
		env_list = env_list->next;
	}
	return (0);
}
