/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:23:33 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/04 15:23:34 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	(void)sig;
	if (g_glob.pid == 1 && g_glob.heredoc != 2)
	{
		if (g_glob.im_in == 1 && g_glob.heredoc != 1)
		{
			printf("\n");
			g_glob.im_in = 0;
			set_ext_stat(130);
		}
		else
		{
			g_glob.check = 1;
			ioctl(0, TIOCSTI, "\n");
			write(1, "\033[A", 3);
			g_glob.heredoc = 2;
			set_ext_stat(1);
		}
		g_glob.quotes = 2;
	}
	else if (g_glob.pid == 0)
	{
		g_glob.check = 1;
		g_glob.heredoc = 2;
		set_ext_stat(1);
	}
}

int	exit_status_fill(t_args **args)
{
	if ((*args)->dlr_arg)
	{
		if ((*args)->dlr_arg->name)
		{
			if ((*args)->dlr_arg->name[0] == '?')
			{
				(*args)->dlr_arg->value = ft_itoa(g_glob.e_status);
				(*args)->dlr_arg->value_l = ft_strlen((*args)->dlr_arg->value);
				return (1);
			}
		}
	}
	return (0);
}

void	set_ext_stat(int i)
{
	g_glob.e_status = i;
	g_glob.ext_tmp = i;
}
