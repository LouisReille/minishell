/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smartsplit_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:56:50 by lreille           #+#    #+#             */
/*   Updated: 2023/02/19 06:14:25 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lock(char *str, char *sign, int i, int d, int s)
{
	while (str[i])
	{
		if (d > 0)
		{
			sign[i - 1] = '\"';
			sign[i] = '\"';
		}
		else if (s > 0)
		{
			sign[i - 1] = '\'';
			sign[i] = '\'';
		}
		else
			sign[i] = ' ';
		i++;
	}
}

char	ft_sep(int d, int s)
{
	char	s1;
	if (d > 0)
		s1 = '\"';
	else if (s > 0)
		s1 = '\'';
	else
		s1 = ' ';
	return (s1);
}

int	ft_nice_squote(char c, int s, int d)
{
	if (c == '\'')
		if (d < 0)
			s = s * -1;
	return (s);
}

int	ft_nice_dquote(char c, int s, int d)
{
	if (c == '\"')
		if (s < 0)
			d = d * -1;
	return (d);
}

char *ft_look(char *str)
{
	int i;
	int d;
	int s;
	char *sign;

	i = 0;
	d = -1;
	s = -1;
	sign = malloc(sizeof(char *) * strlen(str) + 1);
	while(str[i])
	{
		ft_lock(str, sign, i, d, s);
		s = ft_nice_squote(str[i], s, d);
		d = ft_nice_dquote(str[i], s, d);
		i++;
	}
	sign[i] = '\0';
	return (sign);
}

