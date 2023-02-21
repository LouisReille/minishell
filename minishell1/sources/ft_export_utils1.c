/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:43:43 by lreille           #+#    #+#             */
/*   Updated: 2023/02/18 02:44:35 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var(char *str)
{
	char	*s;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str[i] && str[i] != '=')
		i++;
	s = malloc(sizeof(char *) * i + 1);
	while (str[j] && str[j] != '=')
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*get_val(char *str)
{
	char	*s;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	j = 0;
	while (str[i] && str[i++] != '=')
		k++;
	while (str[i++])
		j++;
	s = malloc(sizeof(char *) * j + 1);
	j = k + 1;
	i = 0;
	while (str[j])
		s[i++] = str[j++];
	s[i] = '\0';
	return (s);
}

int	ft_var_position(char **env, char *str)
{
	int	i;
	char	*s;

	i = 0;
	s = ft_cleanvar(str, i);
	while (env[i])
	{
		if (ft_strcmp(get_var(env[i]), s) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_env_dup(char **env)
{
	char	**envd = NULL;
	int	i;

	i = 0;
	envd = malloc(sizeof(char **) * (strlen(*env)) + 1);
	while (env[i])
	{
		envd[i] = strdup(env[i]);
		i++;
	}
	return (envd);
}

char	*ft_add_quotes(char *str)
{
	int	i;
	int	j;
	char	*s;

	i = 0;
	j = 0;
	s = malloc(sizeof(char *) * (strlen(str) + 1));
	s[j] = '\"';
	j++;
	while (str[i])
	{
		s[j] = str[i];
		i++;
		j++;
	}
	s[j] = '\"';
	s[++j] = '\0';
	return (s);
}

