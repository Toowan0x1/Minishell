/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:49:24 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/31 00:14:51 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

// check if is unclosed quotes
static int check_outside(int nbr)
{
   if(nbr % 2 == 0)
        return (0);
    return (1);
}

static int is_unclosed_quotes(char *line)
{
    int double_count;
    int single_count;
    int i;

    double_count = 0;
    single_count = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == '\"')
                if (check_outside(single_count) == 0)
                    double_count++;
        if (line[i] == '\'')
            if (check_outside(double_count) == 0)
                    single_count++;
        i++;
    }
    if (double_count % 2 != 0 || single_count % 2 != 0)
	{
		ft_putstr_fd("minishell: unclosed quotes\n", 2);
        return (1);
	}
    return (0);
}

// echo "hell'o" | wc

int parse(char *line)
{
	if (!line || !(*line))
	{
		g_exit = 10;
		return (0);
	}
	if (check_oper('|', line, 1) || check_oper('<', line, 2) || check_oper('>', line, 2))
	{
		g_exit = 20;
		return (0);
	}
	if (check_oper_in_last(line, '|') || check_oper_in_last(line, '<') || check_oper_in_last(line, '>'))
	{
		g_exit = 30;
		return (0);
	}
	if (check_chars(line,"\\;") || check_pipe(line))
	{
		g_exit = 40;
		return (0);
	}
	if (is_empty(line) || is_unclosed_quotes(line))
	{
		g_exit = 50;
		return (0);
	}
	
	return (1);
}
