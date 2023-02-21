/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:45:44 by lreille           #+#    #+#             */
/*   Updated: 2023/02/19 07:06:49 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_concat(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	i = 0;
	j = 0;
	while (s1[i])
	{
		result[j] = s1[i++];
		j++;
	}
	i = 0;
	result[j] = '/';
	j++;
	while (s2[i])
	{
		result[j] = s2[i++];
		j++;
	}
	result[j] = '\0';
	return (result);
}

void	env_loop(char **command, char *path, char **env)
{
	char	**paths;
	char	*final;
	int		status;
	int		i;
	int		pid;

	i = 0;
	status = 0;
	pid = fork();
	paths = ft_split(path, ':');
	while (paths[i])
	{
		final = ft_concat(paths[i], command[0]);
		if (access(final, F_OK) == 0)
		{
			if (pid == 0)
				execve(final, command, env);
			else
				waitpid(pid, &status, 0);
		}
		i++;
	}
}

int	exec_binary(char **command, char *path, char **env)
{
	char	**paths;
	int		i;
	int		status;

	i = 0;
	status = 0;
	paths = ft_split(path, ':');
	command[0] = ft_strdup(clean_binary_cmd(command[0]));
	if (verif_path(command, path) == 1)
		return (-1);
	env_loop(command, path, env);
	return (0);
}
