/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:36:41 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:43:41 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prev_next(t_list *head)
{
	t_list	*current;
	t_list	*prev;

	current = head;
	prev = NULL;
	while (current != NULL)
	{
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}

void	set_prev_next_ls(t_params *head)
{
	t_params	*current;
	t_params	*prev;

	current = head;
	prev = NULL;
	while (current != NULL)
	{
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}

void	skip_list(t_params **ls_params, int *count)
{
	while ((*ls_params))
	{
		if ((*ls_params)->type == 0)
			(*count)++;
		else
			break ;
		(*ls_params) = (*ls_params)->next;
	}
}
