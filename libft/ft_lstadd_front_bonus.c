/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:46:00 by rturker           #+#    #+#             */
/*   Updated: 2022/10/11 11:19:36 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *nw)
{
	if (!nw)
		return ;
	else if (!lst)
	{
		*lst = nw;
		return ;
	}	
	nw->next = *lst;
	*lst = nw;
}
