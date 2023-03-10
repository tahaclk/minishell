/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:24:58 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/04 15:24:59 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_args *args)
{
	int	i;

	i = 0;
	control_redirections(args);
	while (args->args[i])
	{
		args->args[i] = quote_filter(args->args[i]);
		i++;
	}
}

void	lexer(t_shell *shell, t_args *args)
{
	if (quotes(args, shell->readed_line) == -1)
	{
		printf("Quotes not matched\n");
		g_glob.quotes = -1;
	}
	else
	{
		g_glob.quotes = 1;
		dollar_cleaner(args);
	}
}

void	main_loop(t_shell *shell, t_args *args)
{
	if (g_glob.quotes == 1)
	{
		parser(args);
		execshell(args);
	}
	add_history(shell->readed_line);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_args	args;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	init_program(&shell, &args, envp);
	while (shell.state == 1)
	{
		is_one(&(g_glob.check));
		if (g_glob.heredoc != 2)
		{
			if (main_pre_control(&shell) == -1)
				break ;
			if (!(ft_strlen(shell.readed_line) == 0))
			{
				lexer(&shell, &args);
				main_loop(&shell, &args);
			}
			reset(&args, &shell);
		}
		else
			g_glob.heredoc = 0;
	}
	exit_shell();
}
