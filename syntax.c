/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:53:29 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/04 15:53:30 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_syntax(char *str)
{
	char	c;
	int		i;

	if (str)
	{
		c = str[0];
		if (!ft_isalpha(c) && c != '_')
		{
			printf("minishell: export: `%c': not a valid identifier\n", c);
			return (0);
		}
		i = 1;
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
			{
				printf("minishell: export: `%s': not a valid identifier\n", str);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	pipe_syntax_control(t_list *run_params)
{
	int	i;

	i = 0;
	if (run_params->prev == NULL && ft_strcmp(run_params->content, "|") == 0)
		return (0);
	while (run_params)
	{
		if (ft_strcmp(run_params->content, "|") != 0)
			i = 0;
		else
			i++;
		if (i > 1)
			return (0);
		if (run_params->next == NULL
			&& ft_strcmp(run_params->content, "|") == 0)
			return (0);
		run_params = run_params->next;
	}
	return (1);
}

int	redirection_syntax_control(t_params *ls_params)
{
	while (ls_params)
	{
		if (is_redirection(ls_params->content))
		{
			if (ls_params->next == NULL)
				return (-1);
		}
		else if (is_redirection(ls_params->content) != 0)
		{
			if (is_redirection(ls_params->prev->content)
				|| is_redirection(ls_params->next->content))
			{
				return (-1);
			}
		}
		ls_params = ls_params->next;
	}
	return (1);
}
