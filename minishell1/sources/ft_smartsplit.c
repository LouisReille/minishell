/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smartsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:22:24 by lreille           #+#    #+#             */
/*   Updated: 2023/02/19 06:12:16 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char ft_filter(char *s, int i)
{
	char *str;
	str = ft_look(s);
	return (str[i]);
}

int	ft_nchar(char *str, int i, char c)
{
	size_t	nb;

	nb = 0;
	while (str[i] && str[i] != c)
	{
		nb++;
		i++;
	}
	return (nb);
}

int	ft_word_count(char *str)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
			nb++;
		i++;
	}
	if (str[0] != ft_filter(str, i))
		nb++;
	return (nb);
}

char	**ft_setsmartsplit(char *s, char **str)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] && s[i] == ft_filter(s, i))
			i++;
		else
		{
			str[j] = (char *)malloc(sizeof(char)
			* (ft_nchar(s, i, ft_filter(s, i)) + 1));
			k = 0;
			while (s[i] && s[i] != ft_filter(s, i))
			{
				str[j][k] = s[i];
				k++;
				i++;
			}
			str[j][k] = '\0';
			j++;
		}
	}
	return (str);
}

char	**ft_smartsplit(char *str)
{
	char	**s;
	int	n;

	if (!str)
		return (NULL);
	n = ft_word_count(str);
	s = (char **)malloc(sizeof(char *) * 255);//regerer 255
	if (s == NULL)
		return (NULL);
	s[n + 1] = NULL;
	return (ft_setsmartsplit(str, s));
}
