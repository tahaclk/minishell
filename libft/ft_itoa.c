/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:20:10 by rturker           #+#    #+#             */
/*   Updated: 2022/10/11 11:12:13 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	digit_counter(long n)
{
	long	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	is_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	long	nbr;
	long	length;
	char	*str;

	nbr = n;
	length = digit_counter(nbr);
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	str[length] = '\0';
	length--;
	if (nbr < 0)
		nbr = -nbr;
	while (length >= 0)
	{
		str[length] = (nbr % 10) + '0';
		length--;
		nbr /= 10;
	}
	if (is_sign(n) == 1)
		str[0] = '-';
	return (str);
}
/*
#include <stdio.h>
int main()
{
    printf("%s\n", ft_itoa(-2147483648));
}
*/
/*
#include <stdio.h>
int	main()
{
	char d[] = "-243";
	printf("%s",ft_itoa(-243)[3]);
}
*/
