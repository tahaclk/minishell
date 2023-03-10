/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:37:03 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:43:16 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_fork(int i, int size, t_params *lp)
{
	int	j;
	int	rtn;

	g_glob.pid = 0;
	if (i == 0 && i != size - 1)
		dup2(g_glob.fd[i + 1][1], STDOUT_FILENO);
	else if (i != size - 1)
	{
		dup2(g_glob.fd[i][0], STDIN_FILENO);
		dup2(g_glob.fd[i + 1][1], STDOUT_FILENO);
	}
	else if (size != 1)
		dup2(g_glob.fd[i][0], STDIN_FILENO);
	rtn = re_direc(i, lp);
	j = 0;
	while (j < size)
	{
		close(g_glob.fd[j][0]);
		close(g_glob.fd[j][1]);
		j++;
	}
	if (g_glob.heredoc != 2 && rtn != -1)
		exec_comm(i, lp);
	exit(g_glob.e_status);
}

void	allocate_fd(int *size, t_list **run_params, t_list **tmp, int *i)
{
	*size = (ft_lstsize(*run_params) + 1) / 2;
	g_glob.fd = malloc(sizeof(int *) * (*size));
	*i = -1;
	while (++(*i) < (*size))
	{
		g_glob.fd[*i] = malloc(sizeof(int) * 2);
		if (pipe(g_glob.fd[*i]) == -1)
			return ;
	}
	*tmp = *run_params;
	*i = 0;
}

void	close_fds(int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(g_glob.fd[i][0]);
		close(g_glob.fd[i][1]);
		i++;
	}
}
