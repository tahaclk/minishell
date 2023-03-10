/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:23:50 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/05 12:50:06 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_program(t_shell *shell, t_args *args, char **envp)
{
	g_glob.g_shell = shell;
	g_glob.life = 1;
	shell->state = 1;
	getcwd(shell->path, 4096);
	init_env(envp);
	init_args(args);
	signal(SIGINT, handler);
	g_glob.heredoc = 0;
	g_glob.pid = 1;
	g_glob.check = 0;
	g_glob.im_in = 0;
	args->red_point = NULL;
}

int	init_pipes(int ***fd, t_list *run_params)
{
	int	size;
	int	i;

	size = ((ft_lstsize(run_params) + 1) / 2) - 1;
	*fd = malloc(sizeof(int *) * size);
	i = -1;
	while (++i < size)
	{
		*fd[i] = malloc(sizeof(int) * 2);
		if (pipe(*fd[i]) == -1)
			return (1);
	}
	return (0);
}

void	init_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_glob.env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		g_glob.env[i] = ft_strdup(envp[i]);
	g_glob.env[i] = 0;
}

void	init_prompt(t_shell *shell)
{
	char	*user;

	user = get_env("USER");
	if (user == 0)
		g_glob.user_prompt = "guest@minishell> ";
	else
		g_glob.user_prompt = ft_strjoin(user, "@minishell> ");
	free(user);
	shell->readed_line = readline(g_glob.user_prompt);
}

void	init_args(t_args *args)
{
	t_dollar	dollar;

	args->dlr_arg = &dollar;
	args->dlr_arg->name_l = 0;
	args->dlr_arg->value_l = 0;
	args->i = 0;
	args->size = 0;
	args->wc = 0;
}
