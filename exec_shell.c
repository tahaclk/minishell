/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:21:41 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/05 12:36:55 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_init(t_params **ls_params, t_list **run_params, t_args *args)
{
	t_params	*ls_params_tmp;

	if (g_glob.check == 1)
		return (-1);
	init_params(ls_params, args->args, args->red_point);
	ls_params_tmp = *ls_params;
	*run_params = merge_params(*run_params, ls_params_tmp);
	set_prev_next(*run_params);
	set_prev_next_ls(*ls_params);
	if (redirection_syntax_control(*ls_params) == -1)
	{
		printf("minishell: redirection syntax error\n");
		free_params(*ls_params, *run_params);
		return (-1);
	}
	return (1);
}

void	send_process(int *i, int *size, t_params *lp, t_list **rp)
{
	while (*i < *size)
	{
		if (!is_our_command(go_true_loc(lp, *i)))
			g_glob.im_in = 1;
		heredoc_control(go_true_loc(lp,*i));
		(*rp)->pid = fork();
		if ((*rp)->pid == 0)
			run_fork(*i, *size, lp);
		(*i)++;
		if ((*rp)->next != NULL)
			(*rp) = (*rp)->next->next;
	}
}

void	wait_process(int *i, int *size, t_list **tmp)
{
	close_fds(*size);
	(*i) = 0;
	while ((*i) < *size)
	{
		waitpid((*tmp)->pid, &g_glob.e_status, 0);
		g_glob.e_status = WEXITSTATUS(g_glob.e_status);
		if (g_glob.e_status != g_glob.ext_tmp && g_glob.ext_tmp == 130)
		{
			g_glob.e_status = g_glob.ext_tmp;
			g_glob.ext_tmp = 0;
		}
		(*i)++;
		if ((*tmp)->next != NULL)
			(*tmp) = (*tmp)->next->next;
	}
	g_glob.im_in = 0;
	(*i) = 0;
	while ((*i) < (*size) - 1)
		free(g_glob.fd[(*i)++]);
	free(g_glob.fd);
}

void	execshell(t_args *args)
{
	int			size;
	int			i;
	t_list		*tmp;
	t_params	*ls_params;
	t_list		*run_params;

	if (exec_init(&ls_params, &run_params, args) == -1)
		return ;
	if (first_and_single(ls_params) && pipe_syntax_control(run_params))
	{
		allocate_fd(&size, &run_params, &tmp, &i);
		send_process(&i, &size, ls_params, &run_params);
		wait_process(&i, &size, &tmp);
	}
	else
	{
		if (pipe_syntax_control(run_params))
			exec_comm(0, ls_params);
		else
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			set_ext_stat(258);
		}
	}
	free_params(ls_params, run_params);
}
