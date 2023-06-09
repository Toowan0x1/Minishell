/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:59:27 by oel-houm          #+#    #+#             */
/*   Updated: 2023/06/01 00:02:39 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *env_var, t_env *env_list)
{
	int	env_len;

	if (!env_var)
		return (NULL);
	env_len = ft_strlen(env_var);
	while (env_list->env_name)
	{
		if (ft_strncmp(env_list->env_name, env_var, env_len) == 0)
		{
			return (env_list->env_value);
			break ;
		}
		env_list = env_list->next;
	}
	return (NULL);
}
