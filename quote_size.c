/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:33:08 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/05 12:41:21 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_quote_size(t_args *args, char *str)
{
	int	i;
	int	d_open;
	int	s_open;

	i = -1;
	d_open = 0;
	s_open = 0;
	while (str[++i])
	{
		if (spc_chrc(str[i]) && !s_open && !d_open)
			;
		else if (is_special(str[i]) && !s_open && !d_open)
			lexer_redirection(&i, &(args->size), str[i], str[i + 1]);
		else if (str[i] == '\"' && !s_open && !d_open)
			open_or_close_quotes(&d_open, &(args->size), 1);
		else if (str[i] == '\'' && !s_open && !d_open)
			open_or_close_quotes(&s_open, &(args->size), 1);
		else if (str[i] == '\"' && !s_open && d_open)
			open_quotes_detected(str, &i, &d_open, 1);
		else if (str[i] == '\'' && s_open && !d_open)
			open_quotes_detected(str, &i, &s_open, 2);
		else if (str[i] && !s_open && !d_open)
			if (is_nothing(&(args->size), str, &i) == -1)
				break ;
	}
}

char	*quote_filter(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*word;

	j = 0;
	i = 0;
	word = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] != quote && str[i])
				word[j++] = str[i++];
			i++;
		}
		else
			word[j++] = str[i++];
	}
	word[j] = 0;
	free(str);
	return (re_malloc(word));
}
