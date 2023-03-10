/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:26:26 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/03 18:26:28 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void)
{
	int	i;

	i = 0;
	while (g_glob.env[i])
		free(g_glob.env[i++]);
	free(g_glob.env);
}

void	free_double_pointer(char ***str)
{
	int	i;

	i = 0;
	if ((*str) == NULL)
		return ;
	while ((*str)[i])
		free((*str)[i++]);
	free((*str)[i]);
	free(*str);
}

void	free_t_params(t_params *ls_params)
{
	t_params	*tmp;

	tmp = ls_params;
	if (ls_params)
	{
		while (tmp->next != NULL)
		{
			if (tmp->content)
				free(tmp->content);
			tmp = tmp->next;
		}
		free(tmp->content);
		while (ls_params)
		{
			tmp = ls_params->next;
			free(ls_params);
			ls_params = tmp;
		}
		free(ls_params);
	}
}

void	del(void *param)
{
	free(param);
}

void	free_params(t_params *ls_params, t_list *run_params)
{
	while (ls_params->prev != NULL)
		ls_params = ls_params->prev;
	while (run_params->prev != NULL)
		run_params = run_params->prev;
	free_t_params(ls_params);
	ft_lstclear(&run_params, del);
}
