/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:36:57 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:43:26 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_params *ls_params, char **buffer, char *str)
{
	if (!is_our_command(ls_params))
	{
		if (execve(str, buffer, g_glob.env) == -1)
		{
			if (!access(buffer[1], F_OK))
				printf("minishell: %s: is a directory\n", buffer[1]);
		}
		free_double_pointer(&buffer);
	}
	else
		run_shell(g_glob.g_shell, buffer);
}

void	exec_comm(int i, t_params *ls_params)
{
	char	*str;
	char	**path;
	char	**buffer;

	ls_params = go_true_loc(ls_params, i);
	str = get_env("PATH");
	path = ft_split(str, ':');
	free(str);
	if (ls_params->type == 0)
	{
		buffer = fill_buffer(ls_params);
		tilde_creater(buffer);
		if (access(ls_params->content, F_OK))
			str = find_path(path, ls_params);
		else
			str = ft_strdup(ls_params->content);
		if (str != 0 || is_our_command(ls_params))
			execute(ls_params, buffer, str);
		else
			file_exist(ls_params, buffer);
		free(str);
	}
	free_double_pointer(&path);
}
