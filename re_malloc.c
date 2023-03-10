/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:37:50 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:41:02 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*re_malloc(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	rtn = malloc(ft_strlen(str) + 1);
	if (!rtn)
		return (NULL);
	while (str[i])
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = 0;
	free(str);
	return (rtn);
}
