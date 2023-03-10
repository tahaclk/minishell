/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:08:08 by rturker           #+#    #+#             */
/*   Updated: 2022/10/11 10:20:26 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	j;

	j = 0;
	while (s[j] != (char)c)
	{
		if (s[j] == '\0')
			return (NULL);
		j++;
	}
	return (&((char *)s)[j]);
}
/*
#include <stdio.h>
int main()
{
	char d[] = "heslo";
	printf("%s",ft_strchr(d,'f'));
}
*/
