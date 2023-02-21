/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 09:14:34 by lreille           #+#    #+#             */
/*   Updated: 2023/02/19 07:12:38 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_open_quotes(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	if (command[i - 1][0] == '\'' || command[i - 1][0] == '\"')
	{
		printf("Hello ;) know that quotes should be closed\n");
		return (1);
	}
	return (0);
}

int	verif_path(char **command, char *path)
{
	char	**paths;
	char	*final;
	int		i;
	int		j;

	paths = ft_split(path, ':');
	i = 0;
	j = 0;
	while (paths[i])
	{
		final = ft_concat(paths[i], command[0]);
		if (access(final, F_OK) != 0)
			j++;
		i++;
	}
	if (j == i)
		return (1);
	return (0);
}

char	*clean_command(char **command)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(sizeof(char *) * (ft_strlen(command[0]) + 1));
	i = 0;
	j = 0;
	while (command[0][i])
	{
		if (command[0][i] == '\"' || command[0][i] == '\'')
			i++;
		if (command[0][i] >= 'A' && command[0][i] <= 'Z')
			command[0][i] = command[0][i] + 32;
		str[j] = command[0][i];
		i++;
		j++;
	}
	return (str);
}

char	*clean_binary_cmd(char *command)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char *) * ft_strlen(command) + 1);
	if (ft_strncmp(command, "/bin/", 4) == 0)
	{
		i = 4;
		while (command[i])
		{
			str[j] = command[++i];
			j++;
		}
		return (str);
	}
	else
		return (command);
}
