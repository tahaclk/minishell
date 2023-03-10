/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:36:50 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:43:31 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_env(char *env, t_args *args)
{
	if (ft_strncmp(args->dlr_arg->name, env, args->dlr_arg->name_l))
		return (0);
	return (1);
}

void	env_find(char **env, t_args *args, int *i)
{
	while (env[++(*i)])
		if (compare_env(env[*i], args))
			if (env[*i][args->dlr_arg->name_l] == '=')
				break ;
}
