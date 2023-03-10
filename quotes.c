/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:37:45 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:41:10 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_is_quote(t_args *args, char *str, char quote)
{
	int	close;
	int	mv;

	mv = 0;
	close = 1;
	args->i++;
	while (str[args->i + mv] != quote && str[args->i + mv] != '\0')
		mv++;
	if (str[args->i + mv] == '\0')
		close = 0;
	while (((is_space_or_null(str[args->i + mv]) == 0) || close == 1)
		&& !is_special(str[args->i + mv]))
	{
		if (str[args->i + mv] == quote)
			close = !close;
		mv++;
	}
	args->args[args->wc] = ft_substr(str, args->i - 1, mv + 1);
	while (is_space(str[args->i + mv]) == 1)
		mv++;
	args->i += mv;
	args->wc++;
}

void	quote_out_util(t_args *args, char *str, int *mv, char *mark)
{
	if ((str[args->i + *mv] == '"'
			|| str[args->i + *mv] == '\'') && !(*mark))
	{
		*mark = str[args->i + *mv];
		args->close = !(args->close);
	}
	else if (mark && str[args->i + *mv] == *mark)
	{
		args->close = !(args->close);
		*mark = 0;
	}
	(*mv)++;
}

void	get_is_not_quote(t_args *args, char *str)
{
	int		mv;
	char	mark;

	mv = 0;
	mark = 0;
	args->close = 0;
	while (is_space(str[args->i]) == 1)
		args->i++;
	while ((!is_space_or_null(str[args->i + mv]) || args->close)
		&& (is_special(str[args->i + mv]) == 0 || args->close))
		quote_out_util(args, str, &mv, &mark);
	args->args[args->wc] = ft_substr(str, args->i, mv);
	while (is_space(str[args->i + mv]) == 1)
		mv++;
	args->i += mv;
	args->wc++;
}

void	get_special_args(t_args *args, char *str)
{
	int	mv;

	mv = 0;
	args->i++;
	while (!is_space_or_null(str[args->i + mv]))
	{
		if (mv != 0 || str[args->i + mv] != str[args->i - 1]
			|| isnt_redirect(str[args->i + mv]))
		{
			break ;
		}
		else
			mv++;
	}
	args->args[args->wc] = ft_substr(str, args->i - 1, mv + 1);
	while (is_space(str[args->i + mv]))
		mv++;
	args->i += mv;
	args->wc++;
}

int	quotes(t_args *args, char *str)
{
	if (quotes_is_closed(str))
		return (-1);
	args->size = 0;
	get_quote_size(args, str);
	args->args = (char **)malloc(sizeof(char *) * (args->size + 1));
	res_var(args);
	while (str[args->i])
	{
		if (str[args->i] == '"' || str[args->i] == '\'')
			get_is_quote(args, str, str[args->i]);
		else if (is_special(str[args->i]))
			get_special_args(args, str);
		else
			get_is_not_quote(args, str);
	}
	args->args[args->wc] = NULL;
	return (1);
}
