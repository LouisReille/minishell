/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:41:36 by lreille           #+#    #+#             */
/*   Updated: 2023/02/19 07:11:07 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expart1(char **env, char **str, int nb)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_exportenv(env, str[nb]);
	while (env[i])
	{
		env[i] = new_env[i];
		i++;
	}
}

void	ft_exportrules(char	**command, char **env, int i)
{
	if (command[i] == NULL)
		ft_exportprint(env);
	else
	{
		if (ft_double_strlen(command) > 20)
			printf ("Sorry, can't eat that many arguments\n");
		else
		{
			while (i < ft_double_strlen(command))
				ft_export(env, command[i++]);
		}
	}
}

void	ft_unsetrules(char	**env, char	**command, int i)
{
	while (i < ft_double_strlen(command))
	{
		ft_unset(env, command[i]);
		i++;
	}
}

int	exec_builtins(char **command, char **env, char *input)
{
	int	i;

	i = 1;
	if (ft_strcmp(clean_command(&command[0]), "cd") == 0)
		ft_cd(command);
	else if (ft_strcmp(clean_command(&command[0]), "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(clean_command(&command[0]), "echo") == 0)
		ft_echo(command, env, input);
	else if (ft_strcmp(clean_command(&command[0]), "env") == 0)
		ft_env(env);
	else if (ft_strcmp(clean_command(&command[0]), "unset") == 0)
		ft_unsetrules(env, command, i);
	else if (ft_strcmp(clean_command(&command[0]), "export") == 0)
		ft_exportrules(command, env, i);
	else
		return (-1);
	return (0);
}
