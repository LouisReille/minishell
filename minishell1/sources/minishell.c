/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:36:35 by lreille           #+#    #+#             */
/*   Updated: 2023/02/11 19:27:36 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strlen(env[i]) > 5)
		{
			if (env[i][0] == 'P' && env[i][1] == 'A' &&
				env[i][2] == 'T' && env[i][3] == 'H')
				return (env[i]);
		}
		i++;
	}
	return (NULL);
}

void	sig_handle(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int		ft_exit(char *str)
{
	if (!ft_strcmp(str, "exit"))
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

void	ft_loop(char **env, char **new_env)
{
	char	*input;
	char	**command;

	(void)env;
	signal(SIGINT, sig_handle);
	while (1)
	{	
		input = readline("\033[32mMyMinishell-> $ \033[0m");
		command = ft_smartsplit(input);
		if (command[0] == NULL)
			continue ;
		command[0] = clean_command(command);
		if (ft_exit(command[0]) == 1)
			break ;
		if (exec_builtins(command, new_env, input) == -1)
		{
			if (exec_binary(command, get_path(env) + 5, new_env) == -1)
				printf("mini: %s: command not found\n", command[0]);
		}
		add_history(input);
	}
	signal(SIGQUIT, sig_handle);
}

int	main(int argc, char **argv, char **env)
{
	char	**new_env;
	(void)argv;
	(void)argc;

	new_env = ft_env_dup(env);
	ft_loop(env, new_env);
	return (0);
}
