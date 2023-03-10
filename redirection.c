/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:33:50 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/04 15:33:50 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_r(t_params *ls_params)
{
	int	fd;

	fd = open(ls_params->next->content, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	dup2(fd, 1);
	close(fd);
}

void	redirection_rr(t_params *ls_params)
{
	int	fd;

	fd = open(ls_params->next->content, O_CREAT | O_APPEND | O_WRONLY, 0666);
	dup2(fd, 1);
	close(fd);
}

int	redirection_l(t_params *ls_params)
{
	int	fd;
	int	rtn;

	rtn = 1;
	if (access(ls_params->next->content, F_OK))
	{
		printf("minishell: %s: No such file or directory\n",
			ls_params->next->content);
		set_ext_stat(1);
		rtn = -1;
	}
	fd = open(ls_params->next->content, O_RDONLY, 0666);
	dup2(fd, 0);
	close(fd);
	return (rtn);
}

void	redirection_ll(t_params *ls_params)
{
	char	*key;
	char	*stack;
	int		fd[2];
	int		rtn;

	key = ft_strdup(ls_params->next->content);
	stack = NULL;
	while (1)
	{
		rtn = heredoc_loop(key, &stack);
		if (rtn == 1)
			return ;
		else if (rtn == 0)
			break ;
	}
	pipe(fd);
	ft_putstr_fd(stack, fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	free(stack);
	free(key);
}

int	re_direc(int i, t_params *ls_params)
{
	int			rtn;

	rtn = 1;
	ls_params = go_true_loc(ls_params, i);
	while (ls_params->type != PIPE)
	{
		if (is_redirection(ls_params->content))
		{
			if (ls_params->type == RD_R)
				redirection_r(ls_params);
			else if (ls_params->type == RD_L)
				rtn = redirection_l(ls_params);
			else if (ls_params->type == RD_RR)
				redirection_rr(ls_params);
			else if (ls_params->type == RD_LL)
				redirection_ll(ls_params);
		}
		if (rtn == -1)
			return (-1);
		ls_params = ls_params->next;
		if (ls_params == NULL)
			break ;
	}
	return (rtn);
}
