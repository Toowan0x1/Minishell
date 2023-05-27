/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:15 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/27 00:36:10 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*replace_wrong_name(char *cmd, int *i)
{
	char	*str;
	char	*str2;

	str = ft_strdup(cmd);
	str[*i] = 0;
	str2 = ft_substr(cmd, (*i) + 1, ft_strlenn(cmd));
	free(cmd);
	cmd = ft_strjoin(str, str2);
	*i = ft_strlenn(str);
	free(str);
	free(str2);
	return (cmd);
}

char	*replacing(char *cmd, int *i)
{
	char	*exit;
	char	*str;
	char	*str2;

	exit = ft_itoa(global_exit);
	str = ft_substr(cmd, 0, *i);
	str2 = ft_strjoin(str, exit);
	free(exit);
	free(str);
	str = ft_substr(cmd, (*i) + 2, ft_strlenn(cmd));
	free(cmd);
	cmd = ft_strjoin(str2, str);
	*i = ft_strlenn(str2);
	free(str);
	free(str2);
	return (cmd);
}

void	free_all(char *str, char *str2, char *var_name)
{
	free (str);
	free (str2);
	free (var_name);
}
