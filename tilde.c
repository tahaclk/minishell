/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:38:05 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:40:39 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tilde_util(char *tilde, char *tilde_tmp)
{
	if (access(tilde, F_OK))
	{
		free(tilde);
		tilde = tilde_tmp;
	}
	else
		free(tilde_tmp);
}

void	tilde_creater(char **tilde)
{
	char	*home;
	char	*tmp;
	char	*tilde_tmp;
	int		i;

	if (!tilde)
		return ;
	i = -1;
	while (tilde[++i])
	{
		tilde_tmp = tilde[i];
		if (tilde[i][0] == '~')
		{
			home = get_env("HOME");
			tmp = ft_substr(tilde[i], 1, ft_strlen(tilde[i]) - 1);
			tilde[i] = ft_strjoin(home, tmp);
			free(home);
			free(tmp);
			tilde_util(tilde[i], tilde_tmp);
		}
	}
}
