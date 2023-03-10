/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:55:51 by tcelik            #+#    #+#             */
/*   Updated: 2023/03/04 14:55:52 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_export(char **str)
{
	int	j;

	j = 1;
	if (str[1] == NULL)
		print_export();
	else
	{
		while (str[j])
		{
			if (export_syntax(str[j]))
			{
				if (str[j])
					update_env(str[j], 1);
			}
			else
				set_ext_stat(1);
			j++;
		}
	}
}

void	shell_unset(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i])
			update_env(str[i], -1);
		i++;
	}
}

void	shell_echo(char **args)
{
	int	i;

	i = 0;
	if (!args[i])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(args[i], "-n") == 0)
		i++;
	if (!args[i])
		return ;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (ft_strcmp(args[0], "-n") != 0)
		printf("\n");
}

void	shell_chdir(t_shell *shell, char *dest, char *old_dir)
{
	char	*key;

	getcwd(shell->path, 4096);
	if (!dest)
	{
		key = get_env("HOME");
		if (!key)
			printf("minishell : HOME not set\n");
		chdir(key);
		free(key);
	}
	else
	{
		if (access(dest, X_OK) == 0)
			chdir(dest);
		else if (ENOENT == errno)
		{
			g_glob.e_status = 1;
			g_glob.ext_tmp = 1;
			printf("minishell: cd: %s: No such file or directory\n", dest);
		}
	}
	update_env_pwds(old_dir);
	getcwd(shell->path, 4096);
}

void	run_shell(t_shell *shell, char **buffer)
{
	if (ft_strcmp(buffer[0], "exit") == 0)
		shell->state = -1;
	else
		set_ext_stat(0);
	if (ft_strcmp(buffer[0], "pwd") == 0)
		printf("%s\n", getcwd(shell->path, 4096));
	else if (ft_strcmp(buffer[0], "cd") == 0)
		shell_chdir(shell, buffer[1], shell->path);
	else if (ft_strcmp(buffer[0], "clear") == 0)
		printf("\e[1;1H\e[2J");
	else if (ft_strcmp(buffer[0], "export") == 0)
		shell_export(buffer);
	else if (ft_strcmp(buffer[0], "unset") == 0)
		shell_unset(buffer);
	else if (ft_strcmp(buffer[0], "env") == 0)
		print_env(g_glob.env);
	else if (ft_strcmp(buffer[0], "echo") == 0)
		shell_echo(&buffer[1]);
	free_double_pointer(&buffer);
}
