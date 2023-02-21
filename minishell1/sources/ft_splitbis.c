/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitbis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:57:47 by lreille           #+#    #+#             */
/*   Updated: 2023/02/12 19:11:13 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char	**ft_cmdsep(char *input)
{
	int	i;
	int	j;
	int	k;
	char	sq;
	char	dq;
	char	**splited;

	i = 0;
	j = 0;
	k = 0;
	splited = malloc(sizeof(char **) * 250);
	while (input[i])
	{
		if (input[i] == '\'')
		{
			j = 0;
			sq = '\'';
			i++;
			while (input[i] != sq)
			{
				splited[k][j] = input[i];
				j++;
				i++;
			}
			k++;
		}
		else if (input[i] == '\"')
		{
			j = 0;
			dq = '\"';
			i++;
			while (input[i] != dq)
			{
				splited[k][j] = input[i];
				i++;
				j++;
			}
			k++;
		}
		i++;
	}
	return (splited);
}

int main()
{
	int i = 0;
	char 	*str = "\"coucou      les\"'cocos'";

	char	**s = ft_cmdsep(str);
	while (s[i])
	{
		printf("%d--->%s\n", i, s[i]);
		i++;
	}

	
}
