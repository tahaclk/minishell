/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:21:57 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/05 12:42:17 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_params	*go_true_loc(t_params *ls_params, int i)
{
	int	j;

	j = 0;
	while (j != i)
	{
		if (ls_params->type == PIPE)
			j++;
		ls_params = ls_params->next;
	}
	return (ls_params);
}

t_params	*go_true_loc2(t_params *ls_params)
{
	int	tmp;

	if (ls_params == NULL)
		return (NULL);
	tmp = ls_params->type;
	while (ls_params)
	{
		if (tmp == PIPE)
		{
			if (ls_params->type == PIPE)
				return (ls_params->next);
		}
		else
		{
			if (ls_params->type == PIPE)
				return (ls_params);
		}
		ls_params = ls_params->next;
	}
	return (ls_params);
}

char	*find_path(char **path, t_params *ls_params)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	if (!path)
		return (0);
	while (path[i])
	{
		str = ft_strjoin(path[i], "/");
		tmp = str;
		str = ft_strjoin(tmp, ls_params->content);
		if (!access(str, F_OK))
		{
			free(tmp);
			return (str);
		}
		i++;
		free(tmp);
		free(str);
	}
	return (0);
}

int	find_index(char *str, int c)
{
	int	j;

	j = 0;
	while (str[j] != c)
		j++;
	return (j);
}
