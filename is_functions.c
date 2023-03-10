/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:24:22 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/05 14:16:46 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red_pipe(char *line)
{
	if (ft_strcmp(line, ">") == 0)
		return (1);
	else if (ft_strcmp(line, "<") == 0)
		return (2);
	else if (ft_strcmp(line, ">>") == 0)
		return (3);
	else if (ft_strcmp(line, "<<") == 0)
		return (4);
	else if (ft_strcmp(line, "|") == 0)
		return (5);
	else
		return (0);
}

int	is_redirection(char *line)
{
	if (ft_strcmp(line, ">") == 0)
		return (1);
	else if (ft_strcmp(line, "<") == 0)
		return (2);
	else if (ft_strcmp(line, ">>") == 0)
		return (3);
	else if (ft_strcmp(line, "<<") == 0)
		return (4);
	else
		return (0);
}

int	is_our_command(t_params *ls_params)
{
	if (ft_strcmp(ls_params->content, "exit") == 0)
		return (EXT);
	else if (ft_strcmp(ls_params->content, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(ls_params->content, "cd") == 0)
		return (CD);
	else if (ft_strcmp(ls_params->content, "clear") == 0)
		return (CLEAR);
	else if (ft_strcmp(ls_params->content, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(ls_params->content, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(ls_params->content, "env") == 0)
		return (ENV);
	else if (ft_strcmp(ls_params->content, "echo") == 0)
		return (ECHO);
	return (0);
}

int	is_env_builder(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	is_not_have_dollar_args(t_args *args)
{
	if (!args->dlr_arg)
	{
		args->dlr_arg->value = (char *)malloc(sizeof(char) * 1);
		args->dlr_arg->value[0] = 0;
		args->dlr_arg->value_l = 0;
		return (-1);
	}
	args->dlr_arg->value_l = 0;
	return (0);
}
