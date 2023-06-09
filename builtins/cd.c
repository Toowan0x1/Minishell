/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:23:19 by oel-houm          #+#    #+#             */
/*   Updated: 2023/06/01 22:34:12 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// error manager 
static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static	void	update_pwd_and_oldpwd(char *pwd, t_env *env_list)
{
	char    **export_cwd;
	char    *tmp_arg;

	if (pwd)
	{
		tmp_arg = ft_strjoin("export OLDPWD=", pwd);
		export_cwd = ft_split(tmp_arg, ' ');
		free(tmp_arg);
		//export_cmd(export_cwd, env_list);//export olpwd
		t_env *head_env;
		head_env = env_list;
		//new_env = malloc(sizeof(t_env));
		while (head_env)
		{
			if (ft_strncmp(head_env->env_name, "OLDPWD", strlen("OLDPWD")) == 0)
			{
				free(head_env->env_name);
				free(head_env->env_value);
				head_env->env_name = ft_strdup("OLDPWD");
				head_env->env_value = ft_strdup(pwd);
				head_env->unset = 0;
			}
			head_env = head_env->next;
		}
		free(export_cwd);
		free(pwd);
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		tmp_arg = ft_strjoin("export PWD=", pwd);
		export_cwd = ft_split(tmp_arg, ' ');
		free(tmp_arg);
		//export_cmd(export_cwd, env_list);
		t_env *head_env;
		head_env = env_list;
		//new_env = malloc(sizeof(t_env));
		while (head_env)
		{
			if (ft_strncmp(head_env->env_name, "PWD", strlen("PWD")) == 0)
			{
				free(head_env->env_name);
				free(head_env->env_value);
				head_env->env_name = ft_strdup("PWD");
				head_env->env_value = ft_strdup(pwd);
				head_env->unset = 0;
			}
			head_env = head_env->next;
		}
		free(export_cwd);
		free(pwd);
	}
	else
		perror("minishell: getcwd");
}

//void    cd_home();

void	cd_cmd(char **cmd, t_env *env_list)
{
	int		cd_ret;
	char	*path;
	char	*pwd;

	cd_ret = 0;
	pwd = getcwd(NULL, 0);
	g_exit = 0;
	if (cmd[0] && !cmd[1])
	{
		path = ft_strdup(get_env_value("HOME", env_list));
		if (access(path, F_OK) != -1)
			cd_ret = chdir(path);
		else
			perror("minishell: cd");
		free(path);
	}
	else
	{
		path = ft_strdup(cmd[1]);
		if (ft_strncmp(cmd[1], get_env_value("HOME", env_list),
				ft_strlen(cmd[1] - 1)) == 0)
		{
			printf("***");
			path = ft_strdup(get_env_value("HOME", env_list));
			if (access(path, F_OK) != -1)
				cd_ret = chdir(path);
			else
				perror("minishell: cd");
			free(path);
		}
		else
		{
			cd_ret = chdir(path);
			free(path);
			if (cd_ret < 0)
				cd_ret *= -1;
			if (cd_ret != 0)
				print_error(cmd);
			else
				update_pwd_and_oldpwd(pwd, env_list);
		}
	}
	return ;
}
