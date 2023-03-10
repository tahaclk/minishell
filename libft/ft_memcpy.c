/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:25:24 by rturker           #+#    #+#             */
/*   Updated: 2022/10/10 16:07:39 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst1;
	unsigned char	*src1;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if ((dst1 == 0) && (src1 == 0))
		return (0);
	while (n > 0)
	{
		*(dst1++) = *(src1++);
		n--;
	}
	return (dst);
}

/*
#include <stdio.h>
#include <string.h>
int main(){
    unsigned char str[] = "merhaba";
    unsigned char str2[] = "merhaba";
    memcpy(str,str2+2,5);
    ft_memcpy(str2,str2+2,5);
    printf("str1   :%s\nstr2   :%s\n",str,str2);
    printf("str1   :%s\nstr2   :%s\n",str,str2);
}
*/
