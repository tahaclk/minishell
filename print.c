/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:37:37 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:41:42 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(str[i], '=') != NULL)
			printf("%s\n", str[i]);
	}
}

void	print_export(void)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (g_glob.env[i])
	{
		set_key_and_value(&key, &value, &i);
		if (value != NULL)
			printf("declare -x %s=\"%s\"\n", key, value);
		else if (ft_strchr(g_glob.env[i], '='))
			printf("declare -x %s=\n", key);
		else
			printf("declare -x %s\n", key);
		if (key)
			free(key);
		if (value)
			free(value);
		i++;
	}
}
