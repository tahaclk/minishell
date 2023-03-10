/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:45:09 by rturker           #+#    #+#             */
/*   Updated: 2022/10/11 11:15:41 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->fd_in = -1;
	new->fd_in_tmp = -1;
	new->fd_out_tmp = -1;
	new->fd_out = -1;
	new->pid = -1;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
