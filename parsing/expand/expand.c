/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:12 by wbouwach          #+#    #+#             */
/*   Updated: 2023/06/01 00:49:48 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_all(char *str, char *str2, char *var_name)
{
	free (str);
	free (str2);
	free (var_name);
}

static	char	*replace_var(char *cmd, int *i, t_env *env)
{
	char	*str;
	char	*str2;
	char	*var_name;
	t_env	*find;
	int		end_var;

	str2 = NULL;
	end_var = *i + 1;
	while ((cmd[end_var] && (ft_isalnum(cmd[end_var]) || cmd[end_var] == '_')))
		end_var++;
	var_name = ft_substr(cmd, (*i) + 1, end_var - (*i) - 1);
	find = ft_envlst_search(env, var_name);
	str = ft_substr(cmd, 0, *i);
	if (find && find->env_value)
		str2 = ft_strjoin(str, find->env_value);
	else
		str2 = ft_strjoin(str, "");
	free(str);
	if (cmd[end_var] == '\0')
	{
		end_var -= 1;
		str = ft_strdup(" ");
	}
	else
		str = ft_substr(cmd, end_var, 1000);
	free(cmd);
	cmd = ft_strjoin(str2, str);
	*i = ft_strlenn(str2);
	free_all(str, str2, var_name);
	return (cmd);
}

// replace_var ex 
// echo
// "hi my home dir is"'$HOME'"and and "$HOME
// str = "hi my home dir is"
// str2 = "hi my home dir is"wbouwach
// str = "and and"$HOME
// cmd = "hi my home dir is"wbouwach"and and"$HOME

static	char	*apply_expansion(char *cmd, t_env *env, int *i, int flag)
{
	if (cmd[*i] == '$' && (flag != 1)
		&& (ft_isalnum(cmd[*i + 1]) || cmd[*i + 1] == '_'))
	{
		cmd = replace_var(cmd, i, env);
		if (cmd[*i] == '$' || cmd[*i] == '"' || cmd[*i] == '\'')
			*i -= 1;
		else if (!cmd[*i])
			*i = -2;
	}
	else if (cmd[*i] == '$' && flag != 1)
	{
		cmd = replace_wrong_name(cmd, i);
		if (cmd[*i] == '$' || cmd[*i] == '"' || cmd[*i] == '\'')
			*i -= 1;
		else if (cmd[*i] == '\0')
			*i = -2;
	}
	return (cmd);
}

char	*apply_expander(char *cmd, t_env *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	(void)*env;
	while (cmd[i] && i != -1)
	{
		quoate_flag(&flag,cmd[i]);
		if (cmd[i] == '$' && cmd[i + 1] == '?' && flag != 1)
		{
			cmd = replacing(cmd,&i);
			if (cmd[i] == '$' || cmd[i] == '"' || cmd[i] == '\'')
				continue ;
			else if (cmd[i] == 0)
				break ;
		}
		else if (cmd[i] == '$' && flag != 1
			&& (cmd[i + 1] == '$' || cmd[i + 1] == '\0'))
		{
			i++;
			continue ;
		}
		else
			cmd = apply_expansion(cmd, env, &i, flag);
		i++;
	}
	return (cmd);
}

void	expand(char **cmd, int *token_arr, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
			cmd[i] = apply_expander(cmd[i], env);
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] != ' ' || !(cmd[i][j] >= 9 && cmd[i][j] <= 13))
				break ;
			j++;
		}
		if (!cmd[i][j])
			token_arr[i] = EMPTY;
		i++;
	}
}
/*
echo
 
"hi 'my name is $HOME"
 
|
 
wc
 
>>
 
file
 
*/
