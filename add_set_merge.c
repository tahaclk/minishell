/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_set_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:35:56 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/03 18:35:58 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_params	*add_param(char *parameter, int type)
{
	t_params	*param;

	if (!parameter)
		return (NULL);
	param = (t_params *)malloc(sizeof(t_params));
	param->type = type;
	param->content = ft_strdup(parameter);
	param->next = NULL;
	return (param);
}

void	init_params(t_params **params, char **args, int *rdir_arr)
{
	int			i;
	t_params	*current;

	i = 0;
	*params = NULL;
	current = *params;
	while (args[i])
	{
		if (*params == NULL)
		{
			*params = add_param(args[i], rdir_arr[i]);
			current = *params;
		}
		else
		{
			current->next = add_param(args[i], rdir_arr[i]);
			current = current->next;
		}
		i++;
	}
}

char	*double_join(char *str1, char *str2, char *str3, int mod)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(str1, str2);
	str = ft_strjoin(tmp, str3);
	free(tmp);
	if (mod == 1 && str1)
		free(str1);
	return (str);
}

char	*get_lst_content(t_params *params)
{
	int		swtch;
	char	*str;

	swtch = 0;
	while (params != NULL)
	{
		if (params->next != NULL && params->type != PIPE)
		{
			if (swtch == 0)
			{
				str = double_join(params->content, " ",
						params->next->content, 0);
				swtch = 1;
			}
			else if (params->next->type != PIPE)
				str = double_join(str, " ", params->next->content, 1);
		}
		else if (params->next == NULL && swtch == 0)
			return (ft_strdup(params->content));
		else
			break ;
		params = params->next;
	}
	return (str);
}

t_list	*merge_params(t_list *lst, t_params *params)
{
	int	i;

	i = 0;
	while (params != NULL)
	{
		if (params->type == PIPE)
		{
			if (i == 0)
				lst = ft_lstnew((void *)ft_strdup("|"));
			else
				ft_lstadd_back(&lst, ft_lstnew((void *)ft_strdup("|")));
		}
		else if (params->type != PIPE)
		{
			if (i == 0)
				lst = ft_lstnew((void *)get_lst_content(params));
			else
				ft_lstadd_back(&lst,
					ft_lstnew((void *)get_lst_content(params)));
		}
		i++;
		params = go_true_loc2(params);
	}
	return (lst);
}
