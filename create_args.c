/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:39:25 by rturker           #+#    #+#             */
/*   Updated: 2023/03/05 12:44:20 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_exist(t_params *ls_params, char **buffer)
{
	if (!access(buffer[0], X_OK))
	{
		printf("minishell: %s: is a directory\n", buffer[0]);
		set_ext_stat(126);
	}
	else if (!access(buffer[0], F_OK))
	{
		printf("minishell: %s: permission denied\n", buffer[0]);
		set_ext_stat(126);
	}
	else if (ft_strchr(ls_params->content, '/'))
	{
		printf("minishell: %s: No such file or directory\n", ls_params->content);
		set_ext_stat(127);
	}
	else
	{
		printf("minishell: %s: command not found\n", ls_params->content);
		set_ext_stat(127);
	}
	free_double_pointer(&buffer);
}

char	**creat_args(t_args *args, int i)
{
	int		j;
	int		count;
	char	**buff;

	j = i - 1;
	count = 0;
	while (args->args[i])
	{
		if (args->red_point[i] == 0)
			count++;
		else
			break ;
		i++;
	}
	buff = malloc(sizeof(char *) * count + 1);
	i = 0;
	while (args->args[++j])
	{
		if (args->red_point[j] == 0)
			buff[i++] = args->args[j];
		else
			break ;
	}
	buff[j] = 0;
	return (buff);
}

char	**fill_buffer(t_params *ls_params)
{
	t_params	*tmp;
	int			i;
	int			count;
	char		**buff;

	tmp = ls_params;
	count = 0;
	skip_list(&ls_params, &count);
	buff = malloc(sizeof(char *) * (count + 1));
	ls_params = tmp;
	i = 0;
	while (ls_params)
	{
		if (ls_params->type == 0)
			buff[i++] = ft_strdup(ls_params->content);
		else
			break ;
		ls_params = ls_params->next;
	}
	buff[i] = 0;
	return (buff);
}
