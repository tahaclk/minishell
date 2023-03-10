/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:01:05 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/05 14:17:11 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_and_single(t_params *ls_params)
{
	int			i;
	t_params	*tmp;

	tmp = ls_params;
	i = 0;
	while (tmp)
	{
		if (tmp->type != 0)
			i++;
		tmp = tmp->next;
	}
	if (i == 0 && is_env_builder(ls_params->content))
		return (0);
	return (1);
}

void	heredoc_control(t_params *ls_params)
{
	while (ls_params)
	{
		if (ls_params->type == RD_LL)
			g_glob.heredoc = 1;
		ls_params = ls_params->next;
	}
}

void	control_redirections(t_args *args)
{
	int	i;

	i = 0;
	args->red_point = malloc(sizeof(int) * args->size);
	while (args->args[i])
	{
		if (is_redirection(args->args[i]) == RD_R)
			args->red_point[i] = RD_R;
		else if (is_redirection(args->args[i]) == RD_L)
			args->red_point[i] = RD_L;
		else if (is_redirection(args->args[i]) == RD_RR)
			args->red_point[i] = RD_RR;
		else if (is_redirection(args->args[i]) == RD_LL)
			args->red_point[i] = RD_LL;
		else if (args->args[i][0] == '|')
			args->red_point[i] = PIPE;
		else
			args->red_point[i] = 0;
		i++;
	}
}

int	main_pre_control(t_shell *shell)
{
	init_prompt(shell);
	if (quit_control(shell))
		return (-1);
	return (1);
}
