/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_keyval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:38:00 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:40:54 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_key_and_value(char **key, char **value, int *i)
{
	(*key) = ft_substr(g_glob.env[*i], 0, ft_strchr(g_glob.env[*i], '=')
			- (g_glob.env[*i]));
	if (ft_strchr(g_glob.env[*i], '='))
		(*value) = ft_substr(g_glob.env[*i], ft_strchr(g_glob.env[*i], '=')
				- (g_glob.env[*i]) + 1, ft_strchr(g_glob.env[*i], '=')
				- ft_strchr(g_glob.env[*i], 0));
	else
		(*value) = NULL;
}

void	set_keys(char *keyval, int *find, int *i)
{
	char	*key1;
	char	*key2;

	while (g_glob.env[++(*i)])
	{
		key1 = ft_substr(keyval, 0, ft_strchr(keyval, '=') - keyval);
		key2 = ft_substr(g_glob.env[*i], 0, ft_strchr(g_glob.env[*i], '=')
				- g_glob.env[*i]);
		if (!ft_strcmp(key1, key2))
			(*find)++;
		free(key1);
		free(key2);
	}
}

void	set_tmp(char **tmp, int *i)
{
	if (*tmp)
		free(*tmp);
	*tmp = ft_substr(g_glob.env[*i], ft_strchr(g_glob.env[*i], '=')
			- (g_glob.env[*i]) + 1, ft_strchr(g_glob.env[*i], '=')
			- ft_strchr(g_glob.env[*i], 0));
}

void	set_quote_val(int *s_open, int *d_open, int *counter, int counter_val)
{
	(*s_open) = 0;
	(*d_open) = 0;
	(*counter) = counter_val;
}
