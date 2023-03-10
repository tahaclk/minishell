/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:02:22 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/04 15:02:23 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *key)
{
	int		i;
	char	*tmp;

	if (!g_glob.env)
		return (0);
	i = 0;
	while (g_glob.env[i])
	{
		tmp = ft_substr(g_glob.env[i], 0, ft_strchr(g_glob.env[i], '=')
				- (g_glob.env[i]));
		if (ft_strcmp(key, tmp) == 0)
		{
			set_tmp(&tmp, &i);
			return (tmp);
		}
		if (tmp)
			free(tmp);
		i++;
	}
	return (0);
}

void	add_env_success(char *keyval, char ***tmp, int *i)
{
	char	*key1;
	char	*key2;

	while (g_glob.env[++(*i)])
	{
		if (ft_strchr(keyval, '=') != NULL)
		{
			key1 = ft_substr(keyval, 0, ft_strchr(keyval, '=') - keyval);
			key2 = ft_substr(g_glob.env[*i], 0,
					ft_strchr(g_glob.env[*i], '=') - g_glob.env[*i]);
			if (!ft_strcmp(key1, key2))
				(*tmp)[*i] = ft_strdup(keyval);
			else
				(*tmp)[*i] = ft_strdup(g_glob.env[*i]);
			free(key1);
			free(key2);
		}
		else
			(*tmp)[*i] = ft_strdup(g_glob.env[*i]);
	}
}

void	add_env(char *keyval, char **tmp, int find)
{
	int	i;

	i = -1;
	if (find == 0)
	{
		while (g_glob.env[++i])
			tmp[i] = ft_strdup(g_glob.env[i]);
		tmp[i++] = ft_strdup(keyval);
	}
	else
	{
		add_env_success(keyval, &tmp, &i);
	}
	free_double_pointer(&g_glob.env);
	tmp[i] = 0;
}

void	del_env(char *keyval, char **tmp, int find)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (find == 0)
	{
		while (g_glob.env[++i])
			tmp[i] = ft_strdup(g_glob.env[i]);
	}
	else
	{
		while (g_glob.env[++i])
		{
			if (!ft_strncmp(keyval, g_glob.env[i],
					ft_strchr(g_glob.env[i], '=') - g_glob.env[i]));
			else
				tmp[j++] = ft_strdup(g_glob.env[i]);
		}
	}
	if (find == 0)
		tmp[i] = 0;
	else
		tmp[j] = 0;
	free_double_pointer(&g_glob.env);
}

void	update_env(char *keyval, int state)
{
	char	**tmp;
	int		find;
	int		i;

	find = 0;
	i = -1;
	set_keys(keyval, &find, &i);
	if (state == 1 && find == 0)
		i++;
	else if (state == -1 && find != 0)
		i--;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (state == 1)
		add_env(keyval, tmp, find);
	else if (state == -1)
		del_env(keyval, tmp, find);
	g_glob.env = tmp;
}
