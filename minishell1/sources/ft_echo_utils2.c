/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:37:24 by lreille           #+#    #+#             */
/*   Updated: 2023/02/18 02:38:58 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int		ft_only_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_option_n(char **command)
{
	int	i;
	int	cnt;

	i = 1;
	cnt = 1;
	while (command[i] && command[i][0] == '-')
	{
		if (ft_only_n(command[i]) == 0)
			cnt++;
		if (ft_only_n(command[i]) != 0)
			return (cnt);
		i++;
	}
	return (cnt);
}

char	*ft_cleanvar(char *str, int i)
{
	int	j;
	char	*s;

	j = 0;
	s = malloc(sizeof(char *) * ft_strlen(str) + 1);
	if (str[0] == '$')
		i = i + 1;
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '?'))
	{
		s[j] = str[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*ft_size_cut(char *input, int start, int len)
{
	char	*s;
	int	i;

	i = 0;
	s = malloc(sizeof(char *) * len + 1);
	while (input[start] && i < len)
	{
		s[i] = input[start];
		start++;
		i++;
	}
	s[i] = '\0';
	if (!s)
		return (NULL);
	return (s);
}

int		ft_var_increment_check(char	*str)
{
	if (str[0] == '$')
		return (0);
	else
		return (1);
}
