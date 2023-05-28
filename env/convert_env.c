/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:10:18 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/28 03:45:31 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	count_total_nodes(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list != NULL)
	{
		env_list = env_list->next;
		count++;
	}
	return (count);
}

int	count_total_len(t_env *env_list)
{
	int	total_len;

	total_len = 0;
	total_len += ft_strlen(env_list->env_name);
	total_len += ft_strlen("=");
	total_len += ft_strlen(env_list->env_value);
	return (total_len);
}

void	concat_name_var(char **new_env, t_env *env_list, int i)
{
	char	*tmp;

	new_env[i] = ft_strjoin(env_list->env_name, "=");
	tmp = ft_strdup(new_env[i]);
	free(new_env[i]);
	new_env[i] = ft_strjoin(tmp, env_list->env_value);
	free(tmp);
}

char	**convert_env(t_env *env_list)
{
	char	**new_env;
	int		total_len;
	int		num_of_nodes;
	int		i;

	total_len = 0;
	num_of_nodes = count_total_nodes(env_list);
	new_env = (char **)malloc(sizeof(char *) * (num_of_nodes + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env_list)
	{
		total_len = 0;
		if (env_list->unset == 0)
		{
			total_len = count_total_len(env_list);
			//printf("%d\n", total_len);
			new_env[i] = (char *)malloc(sizeof(char) * (total_len + 1));
			if (!new_env)
				return (NULL);
			concat_name_var(new_env, env_list, i);
		}
		i++;
		env_list = env_list->next;
	}
	new_env[num_of_nodes] = NULL;
	return (new_env);
}
