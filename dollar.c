/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:35:45 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 14:07:40 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_dollar_val(t_args *args)
{
	int		i;
	int		j;
	int		k;
	char	**env;

	env = g_glob.env;
	k = 0;
	i = -1;
	if (exit_status_fill(&args))
		return ;
	env_find(env, args, &i);
	if (is_not_have_dollar_args(args) == -1)
		return ;
	if (!env[i])
		return ;
	j = find_index(env[i], '=');
	k = j;
	while (env[i][++k])
		(args->dlr_arg->value_l)++;
	args->dlr_arg->value = (char *) malloc((args->dlr_arg->value_l + 1));
	k = 0;
	while (env[i][j])
		args->dlr_arg->value[k++] = env[i][j++];
	args->dlr_arg->value[k] = 0;
}

void	fill_dollar_name(t_args *args, int i, int j)
{
	int	len;
	int	k;
	int	x;

	len = 0;
	k = j;
	if (args->args[i][j] == '?')
		len = 1;
	while (args->args[i][j] && is_alnum_us(args->args[i][j]))
	{
		len++;
		j++;
	}
	args->dlr_arg->name = (char *) malloc(sizeof(char) * (len + 1));
	j = k;
	x = 0;
	while (j < k + len)
		args->dlr_arg->name[x++] = args->args[i][j++];
	args->dlr_arg->name[x] = 0;
	args->dlr_arg->name_l = len;
}

void	dollar_replace_with_val(t_args *args, int i, int j)
{
	args->dlr_arg->value = NULL;
	args->dlr_arg->value_l = 0;
	if (ft_isdigit(args->args[i][j]))
		trim_str(args, i);
	else
	{
		fill_dollar_name(args, i, j);
		fill_dollar_val(args);
		trim_str2(args, i, j);
		free(args->dlr_arg->name);
		args->dlr_arg->name = NULL;
		free(args->dlr_arg->value);
		args->dlr_arg->value = NULL;
	}
}

void	change_lock(char quote, int *s_open, int *d_open)
{
	if (quote == '\"' && !(*d_open) && !(*s_open))
		(*d_open) = 1;
	else if (quote == '\'' && !(*d_open) && !(*s_open))
		(*s_open) = 1;
	else if (quote == '"' && (*d_open))
		(*d_open) = 0;
	else if (quote == '\'' && (*s_open))
		(*d_open) = 0;
}

void	dollar_cleaner(t_args *args)
{
	int		i;
	int		j;
	int		let_counter;
	char	*str;

	i = -1;
	str = NULL;
	let_counter = 0;
	while (args->args[++i] && let_counter == 0)
	{
		set_quote_val(&(args->s_open), &(args->d_open), &j, -1);
		while (args->args[i][++j] && str == NULL)
		{
			change_lock(args->args[i][j], &(args->s_open), &(args->d_open));
			if (args->args[i][j] == '$' && !(args->s_open))
			{
				if (is_alnum_us(args->args[i][j + 1]) ||
						args->args[i][j + 1] == '?')
				{
					dollar_replace_with_val(args, i, j + 1);
					set_quote_val(&(args->s_open), &(args->d_open), &j, -1);
				}
			}
		}
	}
}
