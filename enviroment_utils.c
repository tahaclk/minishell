/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:36:43 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:36:44 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwds(char *old_dir, int find)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_glob.env[i])
	{
		if (ft_strncmp(g_glob.env[i], "OLDPWD", 6) == 0 && find != 0)
		{
			free(g_glob.env[i]);
			g_glob.env[i] = ft_strjoin("OLDPWD=", old_dir);
		}
		else if (ft_strncmp(g_glob.env[i], "PWD", 3) == 0)
		{
			tmp = getcwd(NULL, 4096);
			free(g_glob.env[i]);
			g_glob.env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
		}
		i++;
	}
}

void	update_env_pwds(char *old_dir)
{
	int		i;
	int		find;
	char	*tmp;

	find = 0;
	i = -1;
	while (g_glob.env[++i])
		if (ft_strncmp(g_glob.env[i], "OLDPWD", 6) == 0)
			find++;
	if (find == 0)
	{
		tmp = ft_strjoin("OLDPWD=", old_dir);
		update_env(tmp, 1);
		free(tmp);
	}
	set_pwds(old_dir, find);
}
