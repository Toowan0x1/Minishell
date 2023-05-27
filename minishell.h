/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:59:40 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/27 11:28:45 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# define BLUE "\033[1;34m"
# define WHITE "\033[0m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define GNL_BUFFER_SIZE	1
# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define INFILE		0
# define OUTFILE	1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

extern int g_exit;

typedef enum e_token
{
	CMD_NAME = 1,
	CMD_ARG,
	R_IN_SIG,
	R_OUT_SIG,
	R_OUT_FILE,
	PIPE,
	R_APP_SIG,
	R_APP_FILE,
	R_IN_FILE,
	HEREDOC_SIG,
	HEREDOC_LIM,
	EMPTY,
}	t_token;

typedef struct s_env
{
	char    		*env_name;
	char    		*env_value;
	int				unset;
	struct s_env 	*next;
	struct s_env 	*prev;
}	t_env;

typedef	struct	s_cmd_data
{
	char	**parsed_line_args;
	int		num_of_cmds;
	int		*args_tokens;
	char	***cmd;
	int		stdout_copy;
	int		stdin_copy;
	int		i;
} t_cmd_data;

typedef struct s_redirection
{
	/*	INPUT REDIRECTION VARS	*/
	int		in_redirection_token;
	int		in_redirection_index;
	int		infile_index;
	int		in_fd;
	char	*infile;
	/*	OUTPUT REDIRECTION VARS	*/
	int		out_redirection_token;
	int		out_redirection_index;
	int		outfile_index;
	int		out_fd;
	char	*outfile;
	/*	STDIN/STDOUT copy	*/
	int		stdin_copy;
	int		stdout_copy;
}	t_redirection;

typedef struct t_heredoc_data
{
	int		output_redir_token;
	char	*limiter;
	char 	*outfile;
}	t_heredoc_data;




 /* utils  */
int		main(int ac, char **av, char **env);
void	prompt(t_env *env_list);
int		is_redirection(char c);
int		is_space(char c);
int		ft_array_size(char **array_str);
int     ft_envlst_len(t_env *env_list);
int		ft_strlenn(char *s);

/*  ENV  */
t_env	*create_env_list(char **env);
t_env	*ft_envlst_new(char *str);
t_env	*ft_envlst_search(t_env *env, char *searched);

// typedef	struct s_global_vars
// {
// 	char	**parsed_line_args;
// 	int		num_of_cmds;
//     int		*args_tokens;
//     char	***cmd;
//     int		i;
//     int		out_fd;
//     int		stdout_copy;
//     int		stdin_copy;
// }	t_var; // cmd_exec_vars

// typedef struct s_global_vars
// {
// 	int	num_of_cmds;
// }	t_global_vars;


char	**convert_env(t_env *env_list);
void    piping(char **cmd, int infile, int outfile, char **env, t_env *env_list, int *token);
char	*get_cmd_path(char *cmd, char **env);
char	*path_join(char *dir, char *cmd);
char	*get_cmd_path(char *cmd, char **env);
void     exec_builtins(char **cmd, int *tokens, t_env *env_list);
int     is_builtins(char *cmd);
void    exec_cmd(char **cmd_args, char **env);
char    *get_env_value(char *env_var, t_env *env_list);
int		find_env(char *env, t_env *env_list);
void    set_env(char *env_name, char *env_value, t_env *env_list);
void	init_cmd_data(t_cmd_data *cmd_data, char *line);


void	multi_pipes_execution(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list);
void    single_cmd_execution1(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list);
void    single_cmd_execution(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list);
void	execute_line(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list, char *line);



/* DUP INPUT/OUTPUT PIPE */
void	dup_io_before_piping(t_redirection *redirection);
void	dup_output_before_piping(t_redirection *redirection);
void	dup_input_before_piping(t_redirection *redirection);
/* DUP INPUT/OUTPUT PIPE */
void	dup_io_after_piping(t_redirection *redirection);
void	dup_output_after_piping(t_redirection *redirection);
void	dup_input_after_piping(t_redirection *redirection);

/* ESTABLISH BOTH I/O */
void	establish_io_stream(char **cmd, int *cmd_tokens, t_redirection *redirection);

/* ESTABLISH INPUT | OPEN INFILE */
void	establish_input_stream(char **cmd, int *cmd_tokens, t_redirection *redirection);
int		get_infile_index(int *cmd_tokens, int index);
int		get_input_redirection_index(int *cmd_tokens, t_redirection *redirection);
void	set_input_token_to_null(char **cmd, int *cmd_tokens);

/* ESTABLISH OUTPUT / OPEN OUTFILE */
void	establish_output_stream(char **cmd, int *cmd_tokens, t_redirection *redirection);
int		get_outfile_index(int *cmd_tokens, int index);
int		get_output_redirection_index(int *cmd_tokens, t_redirection *redirection);
void	set_output_token_to_null(char **cmd, int *cmd_tokens);

/* GNL */
char	*get_next_line(int fd);
char	*ft_line(char **line, char **str, int fd, int ret);
char	*ft_next(char **line, char **str);

/* HERE_DOC */
void    piping_heredoc(t_heredoc_data *heredoc_data);
int     is_heredoc(char **cmd, int *cmd_token);
void    init_heredoc_data(t_heredoc_data *heredoc_data);
void    set_heredoc_token_to_null(char **cmd, int *cmd_token);
void    get_heredoc_outfile_data(char **cmd, int *cmd_token, t_heredoc_data *heredoc_data);
void    get_heredoc_limiter(char **cmd, int *cmd_token, t_heredoc_data *heredoc_data);

/* ERR_MANAGE */
void    check_argc(int ac);
void    cmd_not_found(char *cmd, int *global_exit);
void	check_fork_fail(pid_t *pid);
void	check_pipe_fail(int *ret);
void	check_dup2_fail(int *ret);

/*  BUILTINS */
void	exit_cmd(char **cmd);
void	pwd_cmd(char **line);
void	unset_cmd(char **cmd, t_env *env_list);
void	echo_cmd(char **line, int *tokens);
void	env_cmd(char **cmd, t_env *env_list);
void    export_cmd(char **cmd, t_env *env_list);
void    cd_cmd(char **cmd, t_env *env_list);

/*  PARSING */
int		parse(char *line);
int		check_pipe(char *line);
int		check_oper(char c, char *line, int nb);
int		check_chars(char *line, char *str);
int		check_unsupport(char *line);
void	quoate_flag(int *flag, int c);
char    *parse_operator(char *line);
char    **args_split(char *cmd);
int		*tokenise_cmd(char **cmd);
int		parse_token(int *token_arr);
void    expand(char **cmd,int *token_arr,t_env *env);
char	*apply_expander(char *cmd, t_env *env);
char    *replacing(char *cmd, int *i);
char	*replace_wrong_name(char *cmd, int *i);
void    delete_quoate(char **cmd);
int		check_oper_in_last(char *line ,char c);
char	***get_piped_cmd_by_ptr(char **cmds, int *tokens);
int		count_cmds(char **cmd, char c);

#endif

