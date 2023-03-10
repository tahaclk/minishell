/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:37:42 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:41:15 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_redirection(int *i, int *size, char c, char d)
{
	if (c == '>' && d == '>')
	{
		(*i)++;
		(*size)++;
	}
	else if (c == '<' && d == '<')
	{
		(*i)++;
		(*size)++;
	}
	else
		(*size)++;
}

void	open_quotes_detected(char *str, int *i, int *quotes, int mod)
{
	if (mod == 1)
	{
		skip_normal_chars(str, i);
		open_or_close_quotes(quotes, i, 2);
	}
	else if (mod == 2)
	{
		open_or_close_quotes(quotes, NULL, 2);
		skip_normal_chars(str, i);
	}
}

void	res_var(t_args *args)
{
	args->i = 0;
	args->wc = 0;
}

void	skip_normal_chars(char *str, int *i)
{
	while (str[*i] && !is_special(str[*i]) && !spc_chrc(str[*i]))
		(*i)++;
}

int	ternary(char expression, char value)
{
	if (expression == value)
		return (0);
	else
		return (1);
}
