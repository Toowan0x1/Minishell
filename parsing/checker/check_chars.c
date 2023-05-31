/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:52:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/06/01 00:13:00 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_chars(char *line, char *str)
{
	int	i;
	int	flag;
	int	j;

	i = 0;
	flag = 0;
	while (line[i])
	{
		j = 0;
		quoate_flag(&flag, line[i]);
		while (flag == 0 && str[j])
		{
			if (line[i] == str[j])
			{
				ft_putstr_fd("minishell: syntax error ", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
