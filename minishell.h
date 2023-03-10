/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:57:25 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/04 15:57:26 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

enum	e_KEYWORDS
{
	CD = 1,
	PWD = 2,
	EXT = 3,
	CLEAR = 4,
	EXPORT = 5,
	UNSET = 6,
	ECHO = 7,
	ENV = 8
};

enum	e_RED_PIPE
{
	RD_R = 1,
	RD_L = 2,
	RD_RR = 3,
	RD_LL = 4,
	PIPE = 5
};

typedef struct s_shell
{
	int		state;
	char	path[4096];
	char	*readed_line;
	int		key_word;
}	t_shell;

typedef struct s_program
{
	t_shell	*g_shell;
	int		life;
	int		e_status;
	int		ext_tmp;
	int		heredoc;
	int		pid;
	int		check;
	int		im_in;
	char	*user_prompt;
	char	**env;
	int		quotes;
	int		**fd;
}	t_program;

t_program	g_glob;

typedef struct s_dollar
{
	int		value_l;
	int		name_l;
	char	*value;
	char	*name;
}	t_dollar;

typedef struct s_args
{
	int			i;
	int			size;
	int			wc;
	int			d_open;
	int			s_open;
	int			close;
	char		**args;
	int			*red_point;
	t_dollar	*dlr_arg;
}	t_args;

typedef struct s_params
{
	char			*content;
	struct s_params	*next;
	struct s_params	*prev;
	int				type;
}	t_params;

void		lexer(t_shell *shell, t_args *args);
void		dollar_cleaner(t_args *args);
void		run_shell(t_shell *shell, char **buffer);
void		init_env(char **envp);
void		print_env(char **str);
void		update_env(char *keyval, int state);
int			quotes(t_args *args, char *str);
int			quotes_is_closed(char *str);
void		quote_args(t_args *args, char *str, char quote);
void		get_quote_size(t_args *args, char *str);
void		get_is_quote(t_args *args, char *str, char quote);
void		get_is_not_quote(t_args *arg, char *str);
void		get_special_args(t_args *arg, char *str);
char		*quote_filter(char *str);
char		*re_malloc(char *str);
void		shell_export(char **str);
void		shell_unset(char **str);
void		update_env_pwds(char *old_dir);
void		handler(int sig);
void		handler2(int sig);
int			is_space(char c);
int			is_special(char c);
int			isnt_redirect(char c);
int			spc_chrc(char c);
void		init_args(t_args *args);
void		quote_out_util(t_args *args, char *str, int *mv, char *mark);
int			double_quote_size(char *str);
int			single_quote_size(char *str);
int			is_space_or_null(char c);
int			is_alnum_us(char c);
int			is_in_quotes(char *str);
int			is_redirection(char *line);
void		control_redirections(t_args *args);
void		init_params(t_params **params, char **args, int *rdir_arr);
void		set_key_and_value(char **key, char **value, int *i);
void		execshell(t_args *args);
t_params	*add_param(char *parameter, int type);
t_list		*merge_params(t_list *lst, t_params *params);
void		send_shell(t_list *param);
int			is_red_pipe(char *line);
void		run_fork(int i, int size, t_params *lp);
void		set_prev_next_ls(t_params *head);
void		set_prev_next(t_list *head);
void		exec_comm(int i, t_params *ls_params);
t_params	*go_true_loc(t_params *ls_params, int i);
int			is_our_command(t_params *ls_params);
char		**fill_buffer(t_params *ls_params);
int			export_syntax(char *str);
char		*find_path(char **path, t_params *ls_params);
char		*get_env(char *key);
void		free_env(void);
int			compare_env(char *env, t_args *args);
void		shell_chdir(t_shell *shell, char *dest, char *old_dir);
void		shell_echo(char **args);
void		free_double_pointer(char ***str);
int			is_env_builder(char *cmd);
int			is_nothing(int *size, char *str, int *i);
int			pipe_syntax_control(t_list *run_params);
int			re_direc(int i, t_params *ls_params);
void		init_params(t_params **params, char **args, int *rdir_arr);
void		init_program(t_shell *shell, t_args *args, char **envp);
int			redirection_syntax_control(t_params *ls_params);
void		free_params(t_params *ls_params, t_list *run_params);
void		free_t_params(t_params *ls_params);
char		*double_join(char *str1, char *str2, char *str3, int mod);
t_params	*go_true_loc2(t_params *ls_params);
int			first_and_single(t_params *ls_params);
void		heredoc_control(t_params *ls_params);
void		init_prompt(t_shell *shell);
void		execute(t_params *ls_params, char **buffer, char *str);
void		file_exist(t_params *ls_params, char **buffer);
int			exit_status_fill(t_args **args);
void		set_ext_stat(int i);
void		lexer_redirection(int *i, int *size, char c, char d);
void		open_or_close_quotes(int *quotes, int *i, int mod);
int			ternary(char expression, char value);
int			heredoc_loop(char *key, char **stack);
void		skip_list(t_params **ls_params, int *count);
void		tilde_creater(char **tilde);
void		is_one(int *i);
int			quit_control(t_shell *shell);
void		reset(t_args *args, t_shell *shell);
void		exit_shell(void);
void		res_var(t_args *args);
void		open_quotes_detected(char *str, int *i, int *quotes, int mod);
void		print_export(void);
void		close_fds(int size);
void		set_tmp(char **tmp, int *i);
void		env_find(char **env, t_args *args, int *i);
int			find_index(char *str, int c);
int			is_not_have_dollar_args(t_args *args);
void		trim_str2(t_args *args, int i, int j);
void		trim_str(t_args *args, int i);
void		set_quote_val(int *s_open, int *d_open, int *c, int counter_val);
void		set_keys(char *keyval, int *find, int *i);
void		allocate_fd(int *size, t_list **run_params, t_list **tmp, int *i);
void		skip_normal_chars(char *str, int *i);
int			main_pre_control(t_shell *shell);
#endif
