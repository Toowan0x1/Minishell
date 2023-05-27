/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:52:38 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/27 01:05:14 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	number_of_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (--count);
}

static	int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	exit_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (number_of_args(cmd) > 1)
	{
		if (cmd[1] && ft_isnum(cmd[1]) != 1)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required this\n", 2);
			exit(255);
		}
		else if (cmd && ft_isnum(cmd[1]) == 1)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		}
	}
	else if (number_of_args(cmd) == 1)
	{
		if (cmd[1][0] == '+' || cmd[1][0] == '-')
			i++;
		if (!(ft_isnum(&cmd[1][i])))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		else
		{
			global_exit = ft_atoi(cmd[1]);
			if (global_exit < 0)
			{
				global_exit = global_exit * -1;
				global_exit = 256 - global_exit;
			}
			ft_putstr_fd("exit\n", 2);
			exit(global_exit);
		}
	}
	else if (number_of_args(cmd) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}
