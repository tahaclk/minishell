/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:39:16 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/03 17:39:19 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_str2(t_args *args, int i, int j)
{
	int		k;
	int		l;
	int		m;
	char	*str;

	k = find_index(args->args[i], '\0');
	str = malloc(k - args->dlr_arg->name_l - 1 + args->dlr_arg->value_l + 1);
	k = 0;
	l = 0;
	while (args->args[i][k])
	{
		if (k == j - 1)
			break ;
		str[l++] = args->args[i][k++];
	}
	m = ternary(args->dlr_arg->name[0], '?');
	if (args->dlr_arg->value)
		while (args->dlr_arg->value[m])
			str[l++] = args->dlr_arg->value[m++];
	k += args->dlr_arg->name_l + 1;
	while (args->args[i][k])
		str[l++] = args->args[i][k++];
	str[l] = 0;
	free(args->args[i]);
	args->args[i] = str;
}

void	trim_str(t_args *args, int i)
{
	int		k;
	int		l;
	char	*str;

	k = 0;
	while (args->args[i][k])
		k++;
	str = (char *) malloc(sizeof(char) * (k - 2 + 1));
	k = 0;
	l = 0;
	while (args->args[i][k])
	{
		if (args->args[i][k] == '$' && ft_isdigit(args->args[i][k + 1]))
			k += 2;
		if (args->args[i][k])
			str[l] = args->args[i][k];
		l++;
		k++;
	}
	str[l] = 0;
	free(args->args[i]);
	args->args[i] = str;
}

int	quotes_is_closed(char *str)
{
	int	i;
	int	d_open;
	int	s_open;

	i = 0;
	d_open = 0;
	s_open = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !s_open && !d_open)
			d_open = 1;
		else if (str[i] == '\'' && !d_open && !s_open)
			s_open = 1;
		else if (str[i] == '\"' && d_open)
			d_open = 0;
		else if (str[i] == '\'' && s_open)
			s_open = 0;
		i++;
	}
	return (d_open || s_open);
}

void	quote_args(t_args *args, char *str, char quote)
{
	int	close;

	close = 1;
	args->i++;
	while (str[args->i] != quote && str[args->i] != '\0')
		args->i++;
	if (str[args->i] == '\0')
		close = 0;
	while (((is_space(str[args->i]) || str[args->i] == '\0') == 0 || close)
		&& !is_special(str[args->i]))
	{
		if (str[args->i] == quote)
			close = !close;
		args->i++;
	}
	while (is_space(str[args->i]))
		args->i++;
	args->size++;
}

void	open_or_close_quotes(int *quotes, int *i, int mod)
{
	if (mod == 1)
	{
		if (quotes != NULL)
			(*quotes) = 1;
		if (i != NULL)
			(*i)++;
	}
	else if (mod == 2)
	{
		if (quotes != NULL)
			(*quotes) = 0;
		if (i != NULL)
			(*i)--;
	}
}
