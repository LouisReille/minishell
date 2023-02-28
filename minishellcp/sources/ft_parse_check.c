/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:14:42 by lreille           #+#    #+#             */
/*   Updated: 2023/02/26 17:15:00 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_sep(char *s, int *index, int *len)
{
	*len = 1;
	if (s[*index] == ' ')
	{
		*len = 0;
		*index = *index + 1;
	}
	if (s[*index] == '>' && s[*index + 1] == '>')
		*len = 2;
	if (s[*index] == '<' && s[*index + 1] == '<')
		*len = 2;
}

int	is_sep(char *str, int index)
{
	if (str[index] == ' ')
		return (1);
	if (str[index] == '<')
		return (1);
	if (str[index] == '>')
		return (1);
	if (str[index] == '|')
		return (1);
	return (0);
}

int	is_quote(char *s, int index)
{
	int	i;
	int	insingle;
	int	indouble;

	i = 0;
	insingle = -1;
	indouble = -1;
	while (s[i] && i <= index)
	{
		if (s[i] == '"' && insingle != 1)
			indouble *= -1;
		if (s[i] == '\'' && indouble != 1)
			insingle *= -1;
		i++;
	}
	if (indouble == 1)
		return (1);
	if (insingle == 1)
		return (2);
	return (0);
}

int	get_type(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0)
		return (RED_I);
	if (ft_strncmp(str, ">", 2) == 0)
		return (RED_O);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (RED_H);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (RED_A);
	if (ft_strncmp(str, "|", 2) == 0)
		return (PIPE);
	return (WORD);
}
